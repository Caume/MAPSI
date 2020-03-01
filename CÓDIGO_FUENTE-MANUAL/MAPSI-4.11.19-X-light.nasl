# Ejemplo de script nasl para identificar puertos de X server abiertos
# Omar Herrera <oherrera@prodigy.net.mx>

if(description)
{
  script_id(99999);
  script_version ("$Revision: 1.0 $");
  script_cve_id("NO CVE ID");

  name["english"] = "X Server port";
  script_name(english:name["english"]);

  desc["english"] = "
X server port open (6000 -6009)

Solution : Use xhost, MIT cookies, and filter incoming TCP connections to this 
port.

Risk factor : Medium to High";

 script_description(english:desc["english"]);

 summary["english"] = "An X Server port is open";
 script_summary(english:summary["english"]);

 script_category(ACT_GATHER_INFO);
 family["english"] = "Misc.";
 family["francais"] = "Divers";
 script_family(english:family["english"], francais:family["francais"]);
 script_dependencie();
 script_copyright(english:"This script is in the public domain.");
 exit(0);
}

#
# The script code starts here
#

for(port=6000; port<6010; port++)
{
  if(get_port_state(port))
  { 
    tcpsock = open_sock_tcp(port);
    if(tcpsock)
    {    
	    report = string("Port: ", port," is open (X server) \n");
          security_warning(port:port, data:report);
   } #if tcpsock
  } #if port open
} #for portnum

exit(0);

