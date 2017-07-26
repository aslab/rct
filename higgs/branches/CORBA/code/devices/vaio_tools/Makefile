install:
	cp -vf higgslog /etc/logrotate.d
	cp -vf restart_servants.conf /etc/acpi/events
	cp -vf restart_servants.sh /etc/acpi/actions
	cp -vf Naming_Service.conf /etc/init
	cp -vf nameservice.ip /etc/higgs
	cp -vf listen_endpoint.ip /etc/higgs
	ln -sf /etc/init.d/Naming_Service /etc/rc2.d/S50Naming_Service
	#adduser higgs
	#adduser higgs dialout

