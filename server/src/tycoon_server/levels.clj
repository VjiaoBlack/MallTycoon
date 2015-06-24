(ns tycoon-server.levels)

(defn sanitize-filename [name]
  (clojure.string/trim
   (clojure.string/replace name #"[\x00-\x1F\/\\:\*\?\"<>\|]" "")))

(defn read [map-name]
  (slurp
   (clojure.java.io/file
    (clojure.java.io/resource "maps")
    (str (sanitize-filename map-name) ".txt"))))
