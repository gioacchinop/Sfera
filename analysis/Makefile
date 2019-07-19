CC = g++
CFLAGS = -Wall -c -g -fpermissive 


INCLUDES = -I. -I.. -I$(ROOTSYS)/include -I$(ROOFIT_INCLUDE)/ 

ROOTSYS ?= ERROR_RootSysIsNotDefined

ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`
ROOTFLAG1 = `${ROOTSYS}/bin/root-config --cflags `

EXTRALIBS := -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG  -lPhysics -lz -lTreePlayer -lRooFitCore -lRooFit


asciiToTree: asciiToTree.cpp 
	$(CC) -Wall $(INCLUDES) -o asciiToTree asciiToTree.cpp $(ROOTFLAG) $(EXTRALIBS)

measToTree: measToTree.cpp 
	$(CC) -Wall $(INCLUDES) -o measToTree measToTree.cpp $(ROOTFLAG) $(EXTRALIBS)

checkPulseShape: checkPulseShape.cpp 
	$(CC) -Wall $(INCLUDES) -o checkPulseShape checkPulseShape.cpp $(ROOTFLAG) $(EXTRALIBS)

makeSpectrum: makeSpectrum.cpp
	$(CC) -Wall $(INCLUDES) -o makeSpectrum makeSpectrum.cpp $(ROOTFLAG) $(EXTRALIBS)

Event: Event.cpp
	$(CC) -c $(INCLUDES) -o Event.o Event.cpp $(ROOTFLAG1) 

Event2: Event2.cpp
	$(CC) -c $(INCLUDES) -o Event2.o Event2.cpp $(ROOTFLAG1) 



DataTree: DataTree.cpp Event.cpp
	$(CC) -c $(INCLUDES) -o DataTree.o DataTree.cpp Event.o $(ROOTFLAG1) 

MeasTree: MeasTree.cpp 
	$(CC) -c $(INCLUDES) -o MeasTree.o MeasTree.cpp $(ROOTFLAG1)

MeasTreeCo: MeasTreeCo.cpp 
	$(CC) -c $(INCLUDES) -o MeasTreeCo.o MeasTreeCo.cpp $(ROOTFLAG1) 



Read_Ttree: Read_Ttree.cpp DataTree.cpp Event.cpp 
	$(CC) -Wall $(INCLUDES) -o Read_Ttree Read_Ttree.cpp DataTree.o Event.o $(ROOTFLAG) $(EXTRALIBS)

Read_TtreeMeas: Read_TtreeMeas.cpp  MeasTree.cpp 
	$(CC) -Wall $(INCLUDES) -o Read_TtreeMeas Read_TtreeMeas.cpp MeasTree.o $(ROOTFLAG) $(EXTRALIBS)

Read_TtreeMeasCo: Read_TtreeMeasCo.cpp  MeasTreeCo.cpp 
	$(CC) -Wall $(INCLUDES) -o Read_TtreeMeasCo Read_TtreeMeasCo.cpp MeasTreeCo.o $(ROOTFLAG) $(EXTRALIBS)





all: asciiToTree checkPulseShape measToTree makeSpectrum Event MeasTree MeasTreeCo DataTree Read_Ttree Read_TtreeMeas Read_TtreeMeasCo


clean:
	rm asciiToTree checkPulseShape measToTree makeSpectrum Event DataTree Read_Ttree MeasTree MeasTreeCo Read_TtreeMeas Read_TtreeMeasCo
 

