
# MessageProcessor

### Problem Statement

Design a MessageProcessor module that reads UDP messages from multiple files with following
format without any gap (i.e. no sequence numbers will be missing) but the packets may be duplicated and out
of sequence.

| Field | DataType | Sample value |
| ------------ | ------------ | ------------ |
| Msg |Type Char | ‘A’|
|SeqNumber|Unsigned long|329231|
|Side |Char |‘B’|
|Size |Unsigned long |2000|
|Ticker|String|“ABC”|
|Price |Double |23.23|

Message Processor should be able to read multiple out of sequence messages files (infile1.txt, infile2.txt) and write back sequenced messages removing duplication in single file outfile.txt.

### Design
- used STL map container to sequence and to avoid duplicates
- Code reads each of the input files and inserts them into map.
- sequenced and uniq map is then written back into output file.

### Build & Run

$ g++ -o MessageProcessor MessageProcessor.cpp -std=c++11
$ g++ -o MessageProcessorMultiThreaded -pthread MessageProcessorMultiThreaded.cpp -std=c++11

$ chmod 777 MessageProcessor MessageProcessorMultiThreaded

$ ./MessageProcessor Infile10.txt Infile13.txt Infile2.txt Infile5.txt Infile8.txt Infile11.txt Infile14.txt  Infile3.txt Infile6.txt Infile9.txt Infile12.txt Infile1.txt Infile4.txt Infile7.txt Outfile.txt

<pre>
Message Processor reading files 
--------------------------------------------------------
readUDPMsgFromFile() :: reading file Infile10.txt
read 27 UDP messages
readUDPMsgFromFile() :: reading file Infile11.txt
read 8 UDP messages
readUDPMsgFromFile() :: reading file Infile12.txt
read 7 UDP messages
readUDPMsgFromFile() :: reading file Infile13.txt
read 7 UDP messages
readUDPMsgFromFile() :: reading file Infile14.txt
read 7 UDP messages
readUDPMsgFromFile() :: reading file Infile1.txt
read 49 UDP messages
readUDPMsgFromFile() :: reading file Infile2.txt
read 63 UDP messages
readUDPMsgFromFile() :: reading file Infile3.txt
read 70 UDP messages
readUDPMsgFromFile() :: reading file Infile4.txt
read 91 UDP messages
readUDPMsgFromFile() :: reading file Infile5.txt
read 112 UDP messages
readUDPMsgFromFile() :: reading file Infile6.txt
read 126 UDP messages
readUDPMsgFromFile() :: reading file Infile7.txt
read 140 UDP messages
readUDPMsgFromFile() :: reading file Infile8.txt
read 147 UDP messages
readUDPMsgFromFile() :: reading file Infile9.txt
read 14 UDP messages
Time taken by function: 56983 microseconds
--------------------------------------------------------
Output Map : (duplicates removed)
printUDPMsgMap(outmap) :: ------------------------------
msg	seqNumber	side	size	ticker	price
A	29238		b	2000	ABC	23.23
B	29239		c	2001	BCD	23.23
C	29240		d	2002	CDE	23.23
D	29241		e	2003	DEF	23.23
E	29242		f	2004	EFG	23.23
F	29243		g	2005	FGH	23.23
G	29244		h	2006	GHI	23.23
A	29245		b	2000	ABC	23.23
B	29246		c	2001	BCD	23.23
C	29247		d	2002	CDE	23.23
D	29248		e	2003	DEF	23.23
E	29249		f	2004	EFG	23.23
F	29250		g	2005	FGH	23.23
G	29251		h	2006	GHI	23.23
A	129231		b	2000	ABC	23.23
B	129232		c	2001	BCD	23.23
C	129233		d	2002	CDE	23.23
D	129234		e	2003	DEF	23.23
E	129235		f	2004	EFG	23.23
F	129236		g	2005	FGH	23.23
G	129237		h	2006	GHI	23.23
A	129238		b	2000	ABC	23.23
B	129239		c	2001	BCD	23.23
C	129240		d	2002	CDE	23.23
D	129241		e	2003	DEF	23.23
E	129242		f	2004	EFG	23.23
F	129243		g	2005	FGH	23.23
G	129244		h	2006	GHI	23.23
A	129245		b	2000	ABC	23.23
B	129246		c	2001	BCD	23.23
C	129247		d	2002	CDE	23.23
D	129248		e	2003	DEF	23.23
E	129249		f	2004	EFG	23.23
F	129250		g	2005	FGH	23.23
G	129251		h	2006	GHI	23.23
D	155558		e	2003	DEF	23.23
A	229238		b	2000	ABC	23.23
B	229239		c	2001	BCD	23.23
C	229240		d	2002	CDE	23.23
D	229241		e	2003	DEF	23.23
E	229242		f	2004	EFG	23.23
F	229243		g	2005	FGH	23.23
G	229244		h	2006	GHI	23.23
A	229245		b	2000	ABC	23.23
B	229246		c	2001	BCD	23.23
C	229247		d	2002	CDE	23.23
D	229248		e	2003	DEF	23.23
E	229249		f	2004	EFG	23.23
F	229250		g	2005	FGH	23.23
G	229251		h	2006	GHI	23.23
C	319247		d	2002	CDE	23.23
B	321246		c	2001	BCD	23.23
A	324245		b	2000	ABC	23.23
G	326251		h	2006	GHI	23.23
A	327245		b	2000	ABC	23.23
B	327246		c	2001	BCD	23.23
C	327247		d	2002	CDE	23.23
E	327249		f	2004	EFG	23.23
G	327251		h	2006	GHI	23.23
D	328248		e	2003	DEF	23.23
A	329238		b	2000	ABC	23.23
B	329239		c	2001	BCD	23.23
C	329240		d	2002	CDE	23.23
D	329241		e	2003	DEF	23.23
E	329242		f	2004	EFG	23.23
F	329243		g	2005	FGH	23.23
G	329244		h	2006	GHI	23.23
A	329245		b	2000	ABC	23.23
B	329246		c	2001	BCD	23.23
C	329247		d	2002	CDE	23.23
D	329248		e	2003	DEF	23.23
E	329249		f	2004	EFG	23.23
F	329250		g	2005	FGH	23.23
G	329251		h	2006	GHI	23.23
A	329345		b	2000	ABC	23.23
A	329445		b	2000	ABC	23.23
A	329545		b	2000	ABC	23.23
A	329845		b	2000	ABC	23.23
A	329945		b	2000	ABC	23.23
E	339249		f	2004	EFG	23.23
E	344449		f	2004	EFG	23.23
F	349250		g	2005	FGH	23.23
A	359245		b	2000	ABC	23.23
C	379247		d	2002	CDE	23.23
A	429245		b	2000	ABC	23.23
B	429246		c	2001	BCD	23.23
C	429247		d	2002	CDE	23.23
D	429248		e	2003	DEF	23.23
E	429249		f	2004	EFG	23.23
F	429250		g	2005	FGH	23.23
G	429251		h	2006	GHI	23.23
A	629238		b	2000	ABC	23.23
B	629239		c	2001	BCD	23.23
C	629240		d	2002	CDE	23.23
D	629241		e	2003	DEF	23.23
E	629242		f	2004	EFG	23.23
F	629243		g	2005	FGH	23.23
G	629244		h	2006	GHI	23.23
A	629245		b	2000	ABC	23.23
B	629246		c	2001	BCD	23.23
C	629247		d	2002	CDE	23.23
D	629248		e	2003	DEF	23.23
E	629249		f	2004	EFG	23.23
F	629250		g	2005	FGH	23.23
G	629251		h	2006	GHI	23.23
A	729245		b	2000	ABC	23.23
B	729246		c	2001	BCD	23.23
C	729247		d	2002	CDE	23.23
D	729248		e	2003	DEF	23.23
E	729249		f	2004	EFG	23.23
F	729250		g	2005	FGH	23.23
G	729251		h	2006	GHI	23.23
A	829231		b	2000	ABC	23.23
B	829232		c	2001	BCD	23.23
C	829233		d	2002	CDE	23.23
D	829234		e	2003	DEF	23.23
E	829235		f	2004	EFG	23.23
F	829236		g	2005	FGH	23.23
G	829237		h	2006	GHI	23.23
A	829238		b	2000	ABC	23.23
B	829239		c	2001	BCD	23.23
C	829240		d	2002	CDE	23.23
D	829241		e	2003	DEF	23.23
E	829242		f	2004	EFG	23.23
F	829243		g	2005	FGH	23.23
G	829244		h	2006	GHI	23.23
A	829245		b	2000	ABC	23.23
B	829246		c	2001	BCD	23.23
C	829247		d	2002	CDE	23.23
D	829248		e	2003	DEF	23.23
E	829249		f	2004	EFG	23.23
F	829250		g	2005	FGH	23.23
G	829251		h	2006	GHI	23.23
A	929231		b	2000	ABC	23.23
B	929232		c	2001	BCD	23.23
C	929233		d	2002	CDE	23.23
D	929234		e	2003	DEF	23.23
E	929235		f	2004	EFG	23.23
F	929236		g	2005	FGH	23.23
G	929237		h	2006	GHI	23.23
A	929238		b	2000	ABC	23.23
B	929239		c	2001	BCD	23.23
C	929240		d	2002	CDE	23.23
D	929241		e	2003	DEF	23.23
E	929242		f	2004	EFG	23.23
F	929243		g	2005	FGH	23.23
G	929244		h	2006	GHI	23.23
A	929245		b	2000	ABC	23.23
B	929246		c	2001	BCD	23.23
C	929247		d	2002	CDE	23.23
D	929248		e	2003	DEF	23.23
E	929249		f	2004	EFG	23.23
F	929250		g	2005	FGH	23.23
G	929251		h	2006	GHI	23.23
154 unique UDP messages in total
</pre>

