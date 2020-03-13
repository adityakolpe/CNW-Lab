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

$n1 shape hexagon
$n2 shape box

$ns at 0.0 "$n0 label shaury"
$ns at 0.0 "$n1 label kolpe"
$ns at 0.0 "$n2 label aditi"
$ns at 0.0 "$n3 label lol"

$ns color 1 Yellow
$ns color 2 Green
$ns color 3 Blue

#link and queue nodes
$ns duplex-link $n0 $n1 1Mb 10ms RED
$ns duplex-link $n1 $n2 1Mb 10ms RED
$ns duplex-link $n2 $n3 1Mb 10ms RED
$ns duplex-link $n3 $n0 1Mb 10ms RED

$ns duplex-link-op $n1 $n0 orient up
$ns duplex-link-op $n1 $n2 orient left
$ns duplex-link-op $n2 $n3 orient up
$ns duplex-link-op $n3 $n0 orient right


set tcp [new Agent/TCP]
set tcpsink [new Agent/TCPSink]
$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $tcpsink
$ns connect $tcp $tcpsink
$tcp set fid_ 1
#create traffic
#FTP
set ftp [new Application/FTP]
$ftp attach-agent $tcp


set tcp1 [new Agent/TCP]
set tcpsink1 [new Agent/TCPSink]
$ns attach-agent $n2 $tcp1
$ns attach-agent $n3 $tcpsink1
$ns connect $tcp1 $tcpsink1
$tcp1 set fid_ 2
#create traffic
#FTP
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1



#finish proc
proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0 }


#disableing a link 
$ns rtmodel-at 1.0 down $n0 $n1
$ns rtmodel-at 2.0 up $n0 $n1

$ns duplex-link-op $n0 $n1 color Green
$ns duplex-link-op $n2 $n3 color Yellow
#scheduling events
$ns at 0.5 "$ftp start"
$ns at 4.5 "$ftp stop"

$ns at 0.5 "$ftp1 start"
$ns at 4.5 "$ftp1 stop"


#call finish proc
$ns at 10.0 "finish"

#run the simiulator
$ns run 
