(ns server.model)

(def player
  {:money 0
   :properties []
   :id 0})

(def property
  {:position [0 0]})

(defn new-player [world]
  (update-in player [:id] (:players world)))

(defn check-action
  [player action]
  (case action
    "BUILD" :ok
    "SAY-NO" :no))
