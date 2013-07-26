
;; (proclaim '(optimize (speed 3) (space 0) (debug 0) (safety 0)))

;(time (write-freq-table (freq-scan "/home/kjell/gnuplot/filter/1/ColumnFamilyClicks-f-7184-Filter.db")
;                        "/tmp/freq-table-lisp"))

(defmacro do-while (test &body body)
  body
  `(do ()
       ((not ,test))
     ,@body))

(defun freq-scan (file)
  (with-open-file (in file :element-type '(unsigned-byte 8))
    (let* ((freq (make-array 256 :element-type '(unsigned-integer 32) :initial-element 0))
	   (length 4096)
	   (buff (make-array length :element-type '(unsigned-byte 8)))
	   (actual-read length))
      (do-while (= length actual-read)
	(setq actual-read (read-sequence buff in :end length))
	(loop for c from 0 to (1- actual-read)
	   do (incf (aref freq (aref buff c)))))
      freq)))

(defun write-freq-table (freq-table filename)
  (with-open-file (out filename
		       :direction :output
		       :if-exists :supersede)
    (with-standard-io-syntax
      (print freq-table out))))
