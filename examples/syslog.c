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
