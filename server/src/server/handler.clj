(ns server.handler
  (:require [manifold.stream :as s]
            [manifold.deferred :as d]
            [clojure.edn :as edn]
            [aleph.tcp :as tcp]
            [gloss.core :as gloss]
            [gloss.io :as io]))

;; Borrowed from `https://github.com/ztellman/aleph/`
(def event-protocol
  " This uses [Gloss](https://github.com/ztellman/gloss), which is a library
  for defining byte formats, which are automatically compiled into encoder and
  streaming decoders. Here, we define a simple protocol where each frame starts
  with a 32-bit integer describing the length of the string which follows. We
  assume the string is EDN-encoded, and so we define a `pre-encoder` of `pr-str`,
  which will turn our arbitrary value into a string, and a `post-decoder` of
  `clojure.edn/read-string`, which will transform our string into a data
  structure."
  (gloss/compile-frame
   (gloss/finite-frame
    (gloss/prefix :uint32)
    (gloss/string :utf-8))
   pr-str
   edn/read-string))

;; Borrowed from `https://github.com/ztellman/aleph/`
(defn wrap-duplex-stream
  "This function takes a raw TCP **duplex stream** which represents bidirectional
  communication via a single stream. Messages from the remote endpoint can be
  consumed via `take!`, and messages can be sent to the remote endpoint via
  `put!`.  It returns a duplex stream which will take and emit arbitrary Clojure
  data, via the protocol we've just defined. First, we define a connection 
  between `out` and the raw stream, which will take all the messages from `out` 
  and encode them before passing them onto the raw stream.

  Then, we `splice` together a separate sink and source, so that they can be 
  presented as a single duplex stream.  We've already defined our sink, which
  will encode all outgoing messages.  We must combine that with a decoded view
  of the incoming stream, which is accomplished via `gloss.io/decode-stream`."
  [protocol s]
  (let [out (s/stream)]
    (s/connect
     (s/map #(io/encode protocol %) out)
     s)
    (s/splice
     out
     (io/decode-stream s protocol))))

(defn event-handler
  [stream info]
  (d/loop []
    (-> (s/take! stream ::none)
        (d/chain
         (fn [msg]
           (if (= ::none msg)
             ::none
             ;; just an example of doing this on another thread
             (d/future (identity "OKAY"))))

         ;; write to client once previous future is completed
         (fn [msg']
           (when-not (= ::none msg')
             (s/put! stream msg')))

         ;; as long as there are no issues, recur!
         (fn [result]
           (when result
             (d/recur))))

        ;; if there are weird errors, write them to the client and close stream
        (d/catch
            (fn [e]
              (s/put! stream (str "Error! " e))
              (s/close! stream))))))

;; Borrowed from `https://github.com/ztellman/aleph/`
(defn client
  "The call to `aleph.tcp/client` returns a deferred, which will yield a duplex 
  stream that can be used to both send and receive bytes. We asynchronously 
  compose over this value using `manifold.deferred/chain`, which will wait for 
  the client to be realized, and then pass the client into `wrap-duplex-stream`.  
  The call to `chain` will return immediately with a deferred value representing 
  the eventual wrapped stream."
  [protocol host port]
  (d/chain (tcp/client {:host host, :port port})
    #(wrap-duplex-stream protocol %)))

(defn start
  "Start our server in the specified port"
  [port]
  (println "Running on port" port)
  (tcp/start-server
   (fn [s info]
     (event-handler (wrap-duplex-stream event-protocol s) info))
   {:port port}))

(defn -main [& args]
  (let [port (or (first args) 8080)]
    (start port)))
