set ns [new Simulator]

#open file for ns tracing
set f [open out.tr w]
$ns trace-all $f

#open file for nam tracing
set nf [open out.nam w]
$ns namtrace-all $nf

#creating nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

#link and queue nodes
$ns duplex-link $n4 $n0 1Mb 10ms RED
$ns duplex-link $n4 $n1 1Mb 10ms RED
$ns duplex-link $n4 $n2 1Mb 10ms RED
$ns duplex-link $n4 $n3 1Mb 10ms RED
#$ns duplex-link/simplex-link $n0 $n1 <bandwidth> <delay> <queuetype>
$ns duplex-link-op $n4 $n0 orient up
$ns duplex-link-op $n4 $n2 orient down
$ns duplex-link-op $n4 $n1 orient right
$ns duplex-link-op $n4 $n3 orient left

#attach agents
set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $n0 $udp
$ns attach-agent $n3 $null
$ns connect $udp $null


set udp1 [new Agent/UDP]
set null1 [new Agent/Null]
$ns attach-agent $n1 $udp1
$ns attach-agent $n2 $null1
$ns connect $udp1 $null1
#create traffic
#FTP
# set ftp [new Application/FTP]
# $ftp attach-agent $tcp
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr attach-agent $udp

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 attach-agent $udp1

#Telnet
#set telnet [new Application/Telnet]
#telnet attach-agent $tcp

#labelling and changing shape


#change colour of link





#finish proc
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0 }


#disableing a link 
#$ns rtmodel-at 1.0 down $n0 $n1
#$ns rtmodel-at 2.0 up $n0 $n1

#scheduling events
$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"

$ns at 0.5 "$cbr1 start"
$ns at 4.0 "$cbr1 stop"


#call finish proc
$ns at 10.0 "finish"

#run the simiulator
$ns run 
