
(cl:in-package :asdf)

(defsystem "higgs_arduino_java-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "TestTwoInts" :depends-on ("_package_TestTwoInts"))
    (:file "_package_TestTwoInts" :depends-on ("_package"))
    (:file "AddTwoInts" :depends-on ("_package_AddTwoInts"))
    (:file "_package_AddTwoInts" :depends-on ("_package"))
  ))