(ns tycoon-server.core
  (:require [aleph.tcp :as tcp]
            [manifold.stream :as s]
            [manifold.deferred :as d]
            [manifold.bus :as bus]))

(defn read-map [map-name]
  (slurp (clojure.java.io/file (clojure.java.io/resource "maps") map-name)))

(defn sputln! [stream x]
  (s/put! stream (str (clojure.string/trim-newline x) "\n")))

(defn handler [stream info]
  (d/loop []
    (-> (s/take! stream ::none)
        (d/chain
         (fn [msg]
           (if (= ::none msg)
             ::none
             (d/future (read-map (clojure.string/trim (String. msg))))))
         (fn [the-map]
           (when-not (= ::none the-map)
             (sputln! stream the-map)))
         (fn [result]
           (when result (d/recur))))

        (d/catch
            (fn [e]
              (s/put! stream (str "ERROR: " e))
              (s/close! stream)))))

  (comment
   (d/let-flow
    [initial-message (s/take! stream)]
    (let [map-name (String. initial-message)]
      (s/put! stream (read-map map-name))))))

(defn -main [& args]
  (let [port (Integer/parseInt (or (first args) "8080"))]
    (println "Starting on port" port)
    (tcp/start-server #'handler {:port port})))
