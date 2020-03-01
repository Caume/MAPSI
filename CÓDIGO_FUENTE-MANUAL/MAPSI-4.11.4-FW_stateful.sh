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
$IPTABLES -P INPUT DROP
$IPTABLES -P FORWARD DROP
$IPTABLES -P OUTPUT ACCEPT

#NAT
#REGLAS DE ENTRADA (INPUT)
  $IPTABLES -A INPUT -p tcp --dport 80 -j ACCEPT
  $IPTABLES -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT
#REGLAS DE REENVÍO (FORWARD)
#REGLAS DE SALIDA (OUTPUT)

#Listado de reglas configuradas
$IPTABLES -L -n -v
$IPTABLES -t nat -L -n -v

