#include 	<syslog.h>
#include	<unistd.h>

int main() {


	int i = setlogmask( LOG_UPTO( LOG_DEBUG ) );

	//setlogmask( LOG_UPTO( LOG_NOTICE ) );

	openlog("syslog_c", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);

	/* 
	 * The following messages will be sent to /var/log/messages 
	 */

	syslog( LOG_EMERG, "Emergency message");
	syslog( LOG_ALERT, "An alert has happened");
	syslog( LOG_CRIT, "A CRITICAL error has happened");
	syslog( LOG_ERR, "An ERROR has hapened");
	syslog( LOG_WARNING, "A WARNING has occurred");
	syslog( LOG_NOTICE, "NOTICE the following");
	syslog( LOG_INFO, "A tree falls in a forest");

	/* 
	 * The following message will be sent to /var/log/debug.log 
	 */

	syslog( LOG_DEBUG, "Used in debugging applications");

	setlogmask( LOG_UPTO( LOG_NOTICE ) );
	closelog();

}

	/*	
	
		NOTE:
		
		You cannot add a new facility to the syslog system as this
		would require changing the syslog.h and the standard library.
		
		Most if not all syslog daemons would also need to be changed
		as they would see other facilities as faulty.
		
		Developers are advised to use LOCAL0 ... LOCAL7 facilities
		instead. 
		
		It is possible however to modify /etc/syslog.conf to redirect
		the LOCAL0 ... LOCAL7 facilities to different files.
		
		For example, to send all your LOCAL0 application logs to 
		the log /var/log/local0 add the following to your config
		file /etc/syslog.conf:
		
		local0.*                                        /var/log/local0
		
	*/
