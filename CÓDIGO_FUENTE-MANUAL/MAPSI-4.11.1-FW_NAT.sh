#!/bin/sh
IPTABLES=/sbin/iptables
#Configura comportamiento de sistema operativo
echo "1" > /proc/sys/net/ipv4/conf/all/rp_filter
echo "1" > /proc/sys/net/ipv4/ip_forward
echo "1" > /proc/sys/net/ipv4/ip_dynaddr
#Borrar reglas anteriores
$IPTABLES -F
$IPTABLES -X
$IPTABLES -t nat -F
$IPTABLES -t nat -X
#Definición de política general
$IPTABLES -P INPUT ACCEPT
$IPTABLES -P FORWARD DROP
$IPTABLES -P OUTPUT ACCEPT
#NAT
SISTEMA_DESTINO=<sist_dest>
$IPTABLES -t nat -A PREROUTING -i eth0 -p ICMP -j DNAT \
 --to-destination $SISTEMA_DESTINO  
#REGLAS DE ENTRADA (INPUT)
#REGLAS DE REENVÍO (FORWARD)
$IPTABLES -A FORWARD -p icmp -o eth0 -j ACCEPT
#REGLAS DE SALIDA (OUTPUT)

#Listado de reglas configuradas
$IPTABLES -L -n -v
$IPTABLES -t nat -L -n -v

