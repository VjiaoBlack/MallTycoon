(defproject server "0.1.0-SNAPSHOT"
  :description "Tycoon server."
  :url "https://github.com/VjiaoBlack/Tycoon"
  :min-lein-version "2.0.0"
  :dependencies [[org.clojure/clojure "1.6.0"]
                 [compojure "1.3.1"]
                 [aleph "0.4.0"]
                 [org.clojure/core.async "0.1.346.0-17112a-alpha"]
                 [gloss "0.2.5"]]
  :main server.handler
  :profiles
  {:dev {:dependencies [[javax.servlet/servlet-api "2.5"]
                        [ring-mock "0.1.5"]]}})
