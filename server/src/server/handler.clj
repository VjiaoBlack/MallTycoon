(ns server.handler
  (:require [compojure.core :refer :all]
            [compojure.route :as route]
            [aleph.http :as http]
            [ring.middleware.params :as params]
            [aleph.http :as http]
            [byte-streams :as bs]
            [manifold.stream :as s]
            [manifold.deferred :as d]
            [manifold.bus :as bus]
            [clojure.core.async :as a]))

(def non-websocket-request
  {:status 400
   :headers {"content-type" "application/text"}
   :body "Erp. I need a websocket request."})

(defn echo-handler
  "Websocket echos."
  [req]
  (-> (http/websocket-connection req)
      (d/chain
       (fn [socket]
         (s/connect socket socket)))
      (d/catch
          (fn [_]
            non-websocket-request))))

(defroutes app-routes
  (GET "/echo" [] echo-handler)
  (route/not-found "Not Found"))

(def app
  app-routes)

(defn start
  "Start our server in the specified port"
  [port]
  (http/start-server app {:port port})
  (println "Running on port" port))

(defn -main [& args]
  (let [port (or (first args) 8080)]
    (start port)))
