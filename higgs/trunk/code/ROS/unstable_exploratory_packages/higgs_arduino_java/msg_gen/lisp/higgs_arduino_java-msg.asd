
(cl:in-package :asdf)

(defsystem "higgs_arduino_java-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "TestDataTypes" :depends-on ("_package_TestDataTypes"))
    (:file "_package_TestDataTypes" :depends-on ("_package"))
    (:file "TestBadDataTypes" :depends-on ("_package_TestBadDataTypes"))
    (:file "_package_TestBadDataTypes" :depends-on ("_package"))
  ))