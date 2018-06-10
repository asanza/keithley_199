v 20130925 2
C 40000 38000 1 90 0 asic-res-4.sym
{
T 39700 39200 5 8 0 0 90 0 1
device=RESISTOR
T 39700 38200 5 10 1 1 90 0 1
value=R17A
T 39700 38700 5 10 0 1 90 0 1
value=1k
}
C 40000 36500 1 90 0 asic-res-4.sym
{
T 39700 37700 5 8 0 0 90 0 1
device=RESISTOR
T 39700 36700 5 10 1 1 90 0 1
refdes=R17B
T 39700 37200 5 10 0 1 90 0 1
value=1k
}
C 41700 36500 1 90 0 asic-res-4.sym
{
T 41400 37700 5 8 0 0 90 0 1
device=RESISTOR
T 41400 36700 5 10 1 1 90 0 1
refdes=R17C
T 41400 37200 5 10 0 1 90 0 1
value=1k
}
C 39400 35300 1 0 0 nmos-3.sym
{
T 40000 35800 5 10 0 0 0 0 1
device=NMOS_TRANSISTOR
T 40400 35900 5 10 1 1 0 0 1
refdes=Q13
}
C 41100 35300 1 0 0 nmos-3.sym
{
T 41700 35800 5 10 0 0 0 0 1
device=NMOS_TRANSISTOR
T 41800 35900 5 10 1 1 0 0 1
refdes=Q3
}
C 43500 34400 1 90 0 nmos-3.sym
{
T 43000 35000 5 10 0 0 90 0 1
device=NMOS_TRANSISTOR
T 42900 35100 5 10 1 1 90 0 1
refdes=Q11
}
C 45100 32600 1 0 0 gnd-1.sym
N 39900 36100 39900 36500 4
N 39900 36300 41600 36300 4
N 41600 36100 41600 36500 4
N 39900 37600 39900 38000 4
N 39900 37800 50900 37800 4
N 41600 37800 41600 37600 4
N 39900 35300 39900 34900 4
N 37500 34900 42700 34900 4
N 41600 34900 41600 35300 4
N 43500 34900 45900 34900 4
N 45200 34900 45200 34100 4
N 45200 33300 45200 32900 4
C 50900 37300 1 270 1 EMBEDDEDnmos-3.sym
[
L 51500 37550 51500 37800 3 0 0 0 -1 -1
L 51100 37550 51100 37800 3 0 0 0 -1 -1
L 51300 37550 51350 37650 3 0 0 0 -1 -1
L 51300 37550 51250 37650 3 0 0 0 -1 -1
P 51100 37300 51100 37500 1 0 0
{
T 51200 37300 5 10 0 1 90 2 1
pinnumber=G
T 51200 37300 9 10 0 1 90 2 1
pinlabel=G
T 51200 37300 5 10 0 0 90 2 1
pinseq=2
T 51200 37300 5 10 0 0 90 2 1
pintype=pas
}
P 51500 37800 51700 37800 1 0 1
{
T 51600 37600 5 10 0 1 90 2 1
pinnumber=D
T 51600 37600 9 10 0 1 90 2 1
pinlabel=D
T 51600 37600 5 10 0 0 90 2 1
pinseq=1
T 51600 37600 5 10 0 0 90 2 1
pintype=pas
}
P 51100 37800 50900 37800 1 0 1
{
T 50900 37600 5 10 0 1 90 2 1
pinnumber=S
T 50900 37600 9 10 0 1 90 2 1
pinlabel=S
T 50900 37600 5 10 0 0 90 2 1
pinseq=3
T 50900 37600 5 10 0 0 90 2 1
pintype=pas
}
L 51575 37550 51425 37550 3 0 0 0 -1 -1
L 51375 37550 51225 37550 3 0 0 0 -1 -1
L 51175 37550 51025 37550 3 0 0 0 -1 -1
L 51500 37500 51100 37500 3 0 0 0 -1 -1
L 51300 37550 51300 37700 3 0 0 0 -1 -1
L 51300 37700 51100 37700 3 0 0 0 -1 -1
T 51400 37900 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 51400 37900 5 10 0 0 90 2 1
numslots=0
T 51400 37900 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 51500 38000 8 10 0 1 90 2 1
refdes=Q?
]
{
T 51400 37900 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 45700 38000 5 10 1 1 90 2 1
refdes=Q35
}
C 45100 39000 1 270 1 EMBEDDEDnmos-3.sym
[
L 45700 39250 45700 39500 3 0 0 0 -1 -1
L 45300 39250 45300 39500 3 0 0 0 -1 -1
L 45500 39250 45550 39350 3 0 0 0 -1 -1
L 45500 39250 45450 39350 3 0 0 0 -1 -1
P 45300 39000 45300 39200 1 0 0
{
T 45400 39000 5 10 0 1 90 2 1
pinnumber=G
T 45400 39000 9 10 0 1 90 2 1
pinlabel=G
T 45400 39000 5 10 0 0 90 2 1
pinseq=2
T 45400 39000 5 10 0 0 90 2 1
pintype=pas
}
P 45700 39500 45900 39500 1 0 1
{
T 45800 39300 5 10 0 1 90 2 1
pinnumber=D
T 45800 39300 9 10 0 1 90 2 1
pinlabel=D
T 45800 39300 5 10 0 0 90 2 1
pinseq=1
T 45800 39300 5 10 0 0 90 2 1
pintype=pas
}
P 45300 39500 45100 39500 1 0 1
{
T 45100 39300 5 10 0 1 90 2 1
pinnumber=S
T 45100 39300 9 10 0 1 90 2 1
pinlabel=S
T 45100 39300 5 10 0 0 90 2 1
pinseq=3
T 45100 39300 5 10 0 0 90 2 1
pintype=pas
}
L 45775 39250 45625 39250 3 0 0 0 -1 -1
L 45575 39250 45425 39250 3 0 0 0 -1 -1
L 45375 39250 45225 39250 3 0 0 0 -1 -1
L 45700 39200 45300 39200 3 0 0 0 -1 -1
L 45500 39250 45500 39400 3 0 0 0 -1 -1
L 45500 39400 45300 39400 3 0 0 0 -1 -1
T 45600 39600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 45600 39600 5 10 0 0 90 2 1
numslots=0
T 45600 39600 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 45700 39700 8 10 0 1 90 2 1
refdes=Q?
]
{
T 45600 39600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 45700 39700 5 10 1 1 90 2 1
refdes=Q30
}
C 42100 39200 1 0 0 Reed-Relay_Meder_SILxx-1A72-71D-2.sym
{
T 42700 39750 5 10 1 1 0 4 1
refdes=K1
T 42100 39900 5 10 0 0 0 0 1
device=Reed-Relay_Meder_SILxx-1A72-71D
T 42100 40100 5 10 0 0 0 0 1
footprint=Reed-Relay_Meder_SILxx-1A72-71D
}
N 39900 39100 39900 43300 4
N 39900 39500 42100 39500 4
N 43300 39500 45100 39500 4
C 38600 35400 1 0 0 input-1.sym
{
T 38600 35700 5 10 1 1 0 0 1
device=1M,30mA
}
C 40300 35400 1 0 0 input-1.sym
{
T 40300 35700 5 10 1 1 0 0 1
device=100K
}
C 40900 33800 1 0 0 input-1.sym
{
T 40900 34100 5 10 1 1 0 0 1
device=1M
}
C 43800 33600 1 0 0 input-1.sym
{
T 43800 33900 5 10 1 1 0 0 1
device=OHM
}
C 44100 39300 1 180 0 input-1.sym
{
T 44100 39000 5 10 1 1 180 0 1
device=3VRelay
}
C 44500 38700 1 0 0 input-1.sym
{
T 44500 39000 5 10 1 1 0 0 1
device=SIG
}
C 50200 36900 1 0 0 input-1.sym
{
T 50200 37200 5 10 1 1 0 0 1
device=ATTEN
}
N 45300 38800 45300 39000 4
N 51000 37000 51100 37000 4
N 51100 37000 51100 37300 4
C 42000 33400 1 0 0 4009-1.sym
{
T 42600 34300 5 10 0 0 0 0 1
device=4009
T 42300 34300 5 10 1 1 0 0 1
refdes=U?
T 42600 37100 5 10 0 0 0 0 1
footprint=DIP16
}
N 43100 33900 43300 33900 4
N 43300 33900 43300 34400 4
N 42000 33900 41700 33900 4
C 40200 43300 1 90 0 Reed-Relay_Meder_SILxx-1A72-71D-2.sym
{
T 39650 43900 5 10 1 1 90 4 1
refdes=K4
T 39500 43300 5 10 0 0 90 0 1
device=Reed-Relay_Meder_SILxx-1A72-71D
T 39300 43300 5 10 0 0 90 0 1
footprint=Reed-Relay_Meder_SILxx-1A72-71D
}
C 40100 44800 1 90 0 capacitor-1.sym
{
T 39400 45000 5 10 0 0 90 0 1
device=CAPACITOR
T 39600 45000 5 10 1 1 90 0 1
refdes=C40
T 39200 45000 5 10 0 0 90 0 1
symversion=0.1
}
N 39900 44500 39900 44800 4
C 40500 45800 1 0 0 Reed-Relay_Meder_SILxx-1A72-71D-2.sym
{
T 41100 46350 5 10 1 1 0 4 1
refdes=K5
T 40500 46500 5 10 0 0 0 0 1
device=Reed-Relay_Meder_SILxx-1A72-71D
T 40500 46700 5 10 0 0 0 0 1
footprint=Reed-Relay_Meder_SILxx-1A72-71D
}
N 40500 46100 39900 46100 4
N 39900 45700 39900 46500 4
C 42200 45500 1 0 0 opamp-1.sym
{
T 42900 46300 5 10 0 0 0 0 1
device=OPAMP
T 42900 46100 5 10 1 1 0 0 1
refdes=U28A
T 42900 46900 5 10 0 0 0 0 1
symversion=0.1
}
N 41700 46100 42200 46100 4
N 43200 45900 45600 45900 4
N 43400 45900 43400 45200 4
N 43400 45200 42200 45200 4
N 42200 45200 42200 45700 4
N 45200 45900 45200 46800 4
C 44600 34100 1 270 0 answitch_spst.sym
{
T 43850 34775 5 10 0 1 270 0 1
device=analog_sw
T 45350 33975 5 10 1 1 270 0 1
refdes=U22A
}
C 44600 47600 1 270 0 answitch_spst.sym
{
T 43850 48275 5 10 0 1 270 0 1
device=analog_sw
T 45350 47475 5 10 1 1 270 0 1
refdes=U21C
}
C 43900 49300 1 0 0 answitch_spst.sym
{
T 43225 48550 5 10 0 1 0 0 1
device=analog_sw
T 44025 50050 5 10 1 1 0 0 1
refdes=U21B
}
C 46500 48100 1 0 0 answitch_spst.sym
{
T 45825 47350 5 10 0 1 0 0 1
device=analog_sw
T 46625 48850 5 10 1 1 0 0 1
refdes=U23B
}
C 45600 45300 1 0 0 answitch_spst.sym
{
T 44925 44550 5 10 0 1 0 0 1
device=analog_sw
T 46225 46050 5 10 1 1 0 0 1
refdes=U23A
}
C 51000 49500 1 0 0 answitch_spst.sym
{
T 50325 48750 5 10 0 1 0 0 1
device=analog_sw
T 51125 50250 5 10 1 1 0 0 1
refdes=U25A
}
C 46600 44800 1 270 0 answitch_spst.sym
{
T 45850 45475 5 10 0 1 270 0 1
device=analog_sw
T 47350 44675 5 10 1 1 270 0 1
refdes=U23D
}
C 38500 50100 1 0 0 answitch_spst.sym
{
T 37825 49350 5 10 0 1 0 0 1
device=analog_sw
T 38625 50850 5 10 1 1 0 0 1
refdes=U21D
}
C 41200 49300 1 0 0 answitch_spst.sym
{
T 40525 48550 5 10 0 1 0 0 1
device=analog_sw
T 41325 50050 5 10 1 1 0 0 1
refdes=U21A
}
C 40000 46500 1 90 0 resistor-1.sym
{
T 39600 46800 5 10 0 0 90 0 1
device=RESISTOR
T 39700 46700 5 10 1 1 90 0 1
refdes=R33
}
C 41200 48400 1 180 1 opamp-1.sym
{
T 41900 47600 5 10 0 0 180 6 1
device=OPAMP
T 41900 47800 5 10 1 1 180 6 1
refdes=U?
T 41900 47000 5 10 0 0 180 6 1
symversion=0.1
}
N 41200 48200 39900 48200 4
N 39900 47400 39900 51700 4
C 40800 47400 1 0 0 gnd-1.sym
N 41200 47800 40900 47800 4
N 40900 47800 40900 47700 4
N 41200 49900 39900 49900 4
C 43500 50000 1 180 0 resistor-1.sym
{
T 43200 49600 5 10 0 0 180 0 1
device=RESISTOR
T 43300 49700 5 10 1 1 180 0 1
refdes=R24
}
C 43500 51800 1 180 0 resistor-1.sym
{
T 43200 51400 5 10 0 0 180 0 1
device=RESISTOR
T 43300 51500 5 10 1 1 180 0 1
refdes=R32
}
C 43500 52600 1 180 0 capacitor-1.sym
{
T 43300 51900 5 10 0 0 180 0 1
device=CAPACITOR
T 43300 52100 5 10 1 1 180 0 1
refdes=C41
T 43300 51700 5 10 0 0 180 0 1
symversion=0.1
}
C 43500 50900 1 180 0 capacitor-1.sym
{
T 43300 50200 5 10 0 0 180 0 1
device=CAPACITOR
T 43300 50400 5 10 1 1 180 0 1
refdes=C43
T 43300 50000 5 10 0 0 180 0 1
symversion=0.1
}
N 42600 49900 42000 49900 4
N 39300 50700 42600 50700 4
N 42300 50700 42300 49900 4
N 42600 51700 39900 51700 4
N 39900 49900 39900 52400 4
N 39900 52400 42600 52400 4
N 43500 48000 43500 52400 4
C 38100 50300 1 0 0 gnd-1.sym
N 38200 50600 38200 50700 4
N 38200 50700 38500 50700 4
C 36900 49400 1 0 0 4009-1.sym
{
T 37500 50300 5 10 0 0 0 0 1
device=4009
T 37200 50300 5 10 1 1 0 0 1
refdes=U?
T 37500 53100 5 10 0 0 0 0 1
footprint=DIP16
}
N 38000 49900 38900 49900 4
N 38900 49900 38900 50100 4
N 42200 48000 43500 48000 4
N 41600 49300 41600 49000 4
N 36200 49000 41600 49000 4
N 36900 49000 36900 49900 4
N 43900 49900 43500 49900 4
N 44700 49900 45700 49900 4
N 45200 49900 45200 47600 4
N 46500 48700 45200 48700 4
C 47500 46500 1 180 1 opamp-1.sym
{
T 48200 45700 5 10 0 0 180 6 1
device=OPAMP
T 48200 45900 5 10 1 1 180 6 1
refdes=U28B
T 48200 45100 5 10 0 0 180 6 1
symversion=0.1
}
C 47100 47000 1 180 0 resistor-1.sym
{
T 46800 46600 5 10 0 0 180 0 1
device=RESISTOR
T 46900 46700 5 10 1 1 180 0 1
refdes=R27
T 46300 47100 5 10 1 1 0 0 1
value=1.002k
}
C 48500 47000 1 180 0 resistor-1.sym
{
T 48200 46600 5 10 0 0 180 0 1
device=RESISTOR
T 48300 46700 5 10 1 1 180 0 1
refdes=R35
T 47800 47100 5 10 1 1 0 0 1
value=9.09k
}
C 46000 46400 1 0 0 gnd-1.sym
N 46100 46700 46100 46900 4
N 46100 46900 46200 46900 4
N 47100 46900 47600 46900 4
N 47400 46900 47400 46300 4
N 47400 46300 47500 46300 4
N 46400 45900 47500 45900 4
N 47300 48700 48500 48700 4
N 48500 48700 48500 46100 4
C 44800 44400 1 0 0 4009-1.sym
{
T 45400 45300 5 10 0 0 0 0 1
device=4009
T 45100 45300 5 10 1 1 0 0 1
refdes=U42A
T 45400 48100 5 10 0 0 0 0 1
footprint=DIP16
}
N 45900 44900 46000 44900 4
N 46000 43800 46000 45300 4
N 44400 44400 46600 44400 4
N 44600 44400 44600 44900 4
N 44600 44900 44800 44900 4
N 47200 44800 47200 45900 4
C 47300 42900 1 90 0 resistor-1.sym
{
T 46900 43200 5 10 0 0 90 0 1
device=RESISTOR
T 47000 43100 5 10 1 1 90 0 1
refdes=R20G
}
C 47100 42400 1 0 0 gnd-1.sym
N 47200 43800 47200 44000 4
N 47200 42900 47200 42700 4
C 45700 50500 1 180 1 opamp-1.sym
{
T 46400 49700 5 10 0 0 180 6 1
device=OPAMP
T 46400 49900 5 10 1 1 180 6 1
refdes=U26B
T 46400 49100 5 10 0 0 180 6 1
symversion=0.1
}
C 43600 44300 1 0 0 input-1.sym
{
T 43600 44600 5 10 1 1 0 0 1
device=/ACA
}
N 46700 50100 48500 50100 4
N 46900 50100 46900 51000 4
N 46900 51000 45700 51000 4
N 45700 51000 45700 50300 4
C 48500 49500 1 0 0 rms_block.sym
{
T 48600 49500 5 10 1 1 0 0 1
refdes=U?
T 49100 49300 5 10 0 1 0 0 1
device=RMS Converter
}
C 53300 49600 1 270 1 EMBEDDEDnmos-3.sym
[
L 53900 49850 53900 50100 3 0 0 0 -1 -1
L 53500 49850 53500 50100 3 0 0 0 -1 -1
L 53700 49850 53750 49950 3 0 0 0 -1 -1
L 53700 49850 53650 49950 3 0 0 0 -1 -1
P 53500 49600 53500 49800 1 0 0
{
T 53600 49600 5 10 0 1 90 2 1
pinnumber=G
T 53600 49600 9 10 0 1 90 2 1
pinlabel=G
T 53600 49600 5 10 0 0 90 2 1
pinseq=2
T 53600 49600 5 10 0 0 90 2 1
pintype=pas
}
P 53900 50100 54100 50100 1 0 1
{
T 54000 49900 5 10 0 1 90 2 1
pinnumber=D
T 54000 49900 9 10 0 1 90 2 1
pinlabel=D
T 54000 49900 5 10 0 0 90 2 1
pinseq=1
T 54000 49900 5 10 0 0 90 2 1
pintype=pas
}
P 53500 50100 53300 50100 1 0 1
{
T 53300 49900 5 10 0 1 90 2 1
pinnumber=S
T 53300 49900 9 10 0 1 90 2 1
pinlabel=S
T 53300 49900 5 10 0 0 90 2 1
pinseq=3
T 53300 49900 5 10 0 0 90 2 1
pintype=pas
}
L 53975 49850 53825 49850 3 0 0 0 -1 -1
L 53775 49850 53625 49850 3 0 0 0 -1 -1
L 53575 49850 53425 49850 3 0 0 0 -1 -1
L 53900 49800 53500 49800 3 0 0 0 -1 -1
L 53700 49850 53700 50000 3 0 0 0 -1 -1
L 53700 50000 53500 50000 3 0 0 0 -1 -1
T 53800 50200 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 53800 50200 5 10 0 0 90 2 1
numslots=0
T 53800 50200 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 53900 50300 8 10 0 1 90 2 1
refdes=Q?
]
{
T 53800 50200 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 53900 50300 5 10 1 1 90 2 1
refdes=Q32
}
N 49600 50100 51000 50100 4
N 51800 50100 53300 50100 4
C 35400 48900 1 0 0 input-1.sym
{
T 35400 49200 5 10 1 1 0 0 1
device=/300VAC-300mA
}
C 44400 48000 1 90 0 input-1.sym
{
T 44100 48000 5 10 1 1 90 0 1
device=/AC ATTEN
}
N 44300 49300 44300 48800 4
C 43100 47100 1 0 0 input-1.sym
{
T 43100 47400 5 10 1 1 0 0 1
device=/3VAC
}
N 43900 47200 44600 47200 4
C 45600 47800 1 0 0 input-1.sym
{
T 45600 48100 5 10 1 1 0 0 1
device=/X10AC
}
N 46400 47900 46900 47900 4
N 46900 47900 46900 48100 4
C 50200 49000 1 0 0 input-1.sym
{
T 50200 49300 5 10 1 1 0 0 1
device=/AC
}
C 52300 49000 1 0 0 input-1.sym
{
T 52300 49300 5 10 1 1 0 0 1
device=MUX
}
N 51000 49100 51400 49100 4
N 51400 49100 51400 49500 4
N 53100 49100 53500 49100 4
N 53500 49100 53500 49600 4
C 45900 34800 1 0 0 asic-res-4.sym
{
T 47100 35100 5 8 0 0 0 0 1
device=RESISTOR
T 46100 35100 5 10 1 1 0 0 1
refdes=R25
T 46600 35100 5 10 0 1 0 0 1
value=1k
}
C 48300 34400 1 270 1 EMBEDDEDnmos-3.sym
[
L 48900 34650 48900 34900 3 0 0 0 -1 -1
L 48500 34650 48500 34900 3 0 0 0 -1 -1
L 48700 34650 48750 34750 3 0 0 0 -1 -1
L 48700 34650 48650 34750 3 0 0 0 -1 -1
P 48500 34400 48500 34600 1 0 0
{
T 48600 34400 5 10 0 1 90 2 1
pinnumber=G
T 48600 34400 9 10 0 1 90 2 1
pinlabel=G
T 48600 34400 5 10 0 0 90 2 1
pinseq=2
T 48600 34400 5 10 0 0 90 2 1
pintype=pas
}
P 48900 34900 49100 34900 1 0 1
{
T 49000 34700 5 10 0 1 90 2 1
pinnumber=D
T 49000 34700 9 10 0 1 90 2 1
pinlabel=D
T 49000 34700 5 10 0 0 90 2 1
pinseq=1
T 49000 34700 5 10 0 0 90 2 1
pintype=pas
}
P 48500 34900 48300 34900 1 0 1
{
T 48300 34700 5 10 0 1 90 2 1
pinnumber=S
T 48300 34700 9 10 0 1 90 2 1
pinlabel=S
T 48300 34700 5 10 0 0 90 2 1
pinseq=3
T 48300 34700 5 10 0 0 90 2 1
pintype=pas
}
L 48975 34650 48825 34650 3 0 0 0 -1 -1
L 48775 34650 48625 34650 3 0 0 0 -1 -1
L 48575 34650 48425 34650 3 0 0 0 -1 -1
L 48900 34600 48500 34600 3 0 0 0 -1 -1
L 48700 34650 48700 34800 3 0 0 0 -1 -1
L 48700 34800 48500 34800 3 0 0 0 -1 -1
T 48800 35000 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 48800 35000 5 10 0 0 90 2 1
numslots=0
T 48800 35000 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 48900 35100 8 10 0 1 90 2 1
refdes=Q?
]
{
T 48800 35000 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 48900 35100 5 10 1 1 90 2 1
refdes=Q33
}
N 47000 34900 48300 34900 4
C 47200 33200 1 0 0 4009-1.sym
{
T 47800 34100 5 10 0 0 0 0 1
device=4009
T 47500 34100 5 10 1 1 0 0 1
refdes=U?
T 47800 36900 5 10 0 0 0 0 1
footprint=DIP16
}
C 46000 33600 1 0 0 input-1.sym
{
T 46000 33900 5 10 1 1 0 0 1
device=/1M Sense
}
N 46800 33700 47200 33700 4
N 48300 33700 48500 33700 4
N 48500 33700 48500 34400 4
C 37200 38300 1 270 0 Reed-Relay_Meder_SILxx-1A72-71D-2.sym
{
T 37750 37700 5 10 1 1 270 4 1
refdes=K3
T 37900 38300 5 10 0 0 270 0 1
device=Reed-Relay_Meder_SILxx-1A72-71D
T 38100 38300 5 10 0 0 270 0 1
footprint=Reed-Relay_Meder_SILxx-1A72-71D
}
N 37500 34900 37500 37100 4
N 37500 38300 37500 39500 4
N 35900 39500 39900 39500 4
C 35100 39400 1 0 0 input-1.sym
{
T 35100 39700 5 10 1 1 0 0 1
device=Volt Ohm Hi input
}
C 35600 36900 1 0 0 input-1.sym
{
T 35600 37200 5 10 1 1 0 0 1
device=OHM Relay
}
N 36400 37000 37200 37000 4
N 37200 37000 37200 37100 4
C 48300 36000 1 270 1 EMBEDDEDnmos-3.sym
[
L 48900 36250 48900 36500 3 0 0 0 -1 -1
L 48500 36250 48500 36500 3 0 0 0 -1 -1
L 48700 36250 48750 36350 3 0 0 0 -1 -1
L 48700 36250 48650 36350 3 0 0 0 -1 -1
P 48500 36000 48500 36200 1 0 0
{
T 48600 36000 5 10 0 1 90 2 1
pinnumber=G
T 48600 36000 9 10 0 1 90 2 1
pinlabel=G
T 48600 36000 5 10 0 0 90 2 1
pinseq=2
T 48600 36000 5 10 0 0 90 2 1
pintype=pas
}
P 48900 36500 49100 36500 1 0 1
{
T 49000 36300 5 10 0 1 90 2 1
pinnumber=D
T 49000 36300 9 10 0 1 90 2 1
pinlabel=D
T 49000 36300 5 10 0 0 90 2 1
pinseq=1
T 49000 36300 5 10 0 0 90 2 1
pintype=pas
}
P 48500 36500 48300 36500 1 0 1
{
T 48300 36300 5 10 0 1 90 2 1
pinnumber=S
T 48300 36300 9 10 0 1 90 2 1
pinlabel=S
T 48300 36300 5 10 0 0 90 2 1
pinseq=3
T 48300 36300 5 10 0 0 90 2 1
pintype=pas
}
L 48975 36250 48825 36250 3 0 0 0 -1 -1
L 48775 36250 48625 36250 3 0 0 0 -1 -1
L 48575 36250 48425 36250 3 0 0 0 -1 -1
L 48900 36200 48500 36200 3 0 0 0 -1 -1
L 48700 36250 48700 36400 3 0 0 0 -1 -1
L 48700 36400 48500 36400 3 0 0 0 -1 -1
T 48800 36600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 48800 36600 5 10 0 0 90 2 1
numslots=0
T 48800 36600 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 48900 36700 8 10 0 1 90 2 1
refdes=Q?
]
{
T 48800 36600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 48900 36700 5 10 1 1 90 2 1
refdes=Q34
}
N 48300 36500 45200 36500 4
N 45200 36500 45200 34900 4
C 47000 35600 1 0 0 input-1.sym
{
T 47000 35900 5 10 1 1 0 0 1
device=100K Sense
}
N 47800 35700 48500 35700 4
N 48500 35700 48500 36000 4
C 45100 41000 1 270 1 EMBEDDEDnmos-3.sym
[
L 45700 41250 45700 41500 3 0 0 0 -1 -1
L 45300 41250 45300 41500 3 0 0 0 -1 -1
L 45500 41250 45550 41350 3 0 0 0 -1 -1
L 45500 41250 45450 41350 3 0 0 0 -1 -1
P 45300 41000 45300 41200 1 0 0
{
T 45400 41000 5 10 0 1 90 2 1
pinnumber=G
T 45400 41000 9 10 0 1 90 2 1
pinlabel=G
T 45400 41000 5 10 0 0 90 2 1
pinseq=2
T 45400 41000 5 10 0 0 90 2 1
pintype=pas
}
P 45700 41500 45900 41500 1 0 1
{
T 45800 41300 5 10 0 1 90 2 1
pinnumber=D
T 45800 41300 9 10 0 1 90 2 1
pinlabel=D
T 45800 41300 5 10 0 0 90 2 1
pinseq=1
T 45800 41300 5 10 0 0 90 2 1
pintype=pas
}
P 45300 41500 45100 41500 1 0 1
{
T 45100 41300 5 10 0 1 90 2 1
pinnumber=S
T 45100 41300 9 10 0 1 90 2 1
pinlabel=S
T 45100 41300 5 10 0 0 90 2 1
pinseq=3
T 45100 41300 5 10 0 0 90 2 1
pintype=pas
}
L 45775 41250 45625 41250 3 0 0 0 -1 -1
L 45575 41250 45425 41250 3 0 0 0 -1 -1
L 45375 41250 45225 41250 3 0 0 0 -1 -1
L 45700 41200 45300 41200 3 0 0 0 -1 -1
L 45500 41250 45500 41400 3 0 0 0 -1 -1
L 45500 41400 45300 41400 3 0 0 0 -1 -1
T 45600 41600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 45600 41600 5 10 0 0 90 2 1
numslots=0
T 45600 41600 5 10 0 0 90 2 1
description=generic N channel MOS transistor (enhancement type)
T 45700 41700 8 10 0 1 90 2 1
refdes=Q?
]
{
T 45600 41600 5 10 0 0 90 2 1
device=NMOS_TRANSISTOR
T 45700 41700 5 10 1 1 90 2 1
refdes=Q12
}
C 43700 41400 1 0 0 input-1.sym
{
T 43700 41700 5 10 1 1 0 0 1
device=+5V
}
C 43700 40400 1 0 0 input-1.sym
{
T 43700 40700 5 10 1 1 0 0 1
device=OHM
}
N 44500 41500 45100 41500 4
N 44500 40500 45300 40500 4
N 45300 40500 45300 41000 4
C 45100 42600 1 90 0 diode-1.sym
{
T 44500 43000 5 10 0 0 90 0 1
device=DIODE
T 44600 42900 5 10 1 1 90 0 1
refdes=CR12
}
N 44900 42600 44900 40500 4
N 44900 43500 44900 43800 4
N 44900 43800 46000 43800 4
N 54100 50100 54500 50100 4
N 54500 34900 54500 50100 4
N 54500 34900 49100 34900 4
N 49100 36500 54500 36500 4
N 51700 37800 54500 37800 4
N 45900 39500 54500 39500 4
N 45900 41500 49300 41500 4
N 49300 41500 49300 37800 4
C 40300 42100 1 90 0 input-1.sym
{
T 40600 42100 5 10 1 1 90 0 1
device=ACV Relay
}
N 40200 42900 40200 43300 4
C 42000 44500 1 90 0 input-1.sym
{
T 41700 44500 5 10 1 1 90 0 1
device=3VARelay
}
N 41700 45800 41900 45800 4
N 41900 45800 41900 45300 4
