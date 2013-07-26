 freq_scan.core
  (:gen-class)
  (:require clojure.java.io
            clojure.pprint))

(defn -main [& args]
  (when (empty? args)
    (println "Need a file as first parameter.")
    (System/exit 1))
  (let [freqs (int-array 256 0)]
    (with-open [r (clojure.java.io/reader (first args))]
      (doseq [line (line-seq r)]
;;        (doall (for [c line] (aset freqs c (inc (aget freqs c)))))))
        (doall (for [c (.getBytes line)] (aset freqs c (inc (aget freqs c)))))))
    (clojure.pprint/pprint freqs)))
