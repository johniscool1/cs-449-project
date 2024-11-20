       IDENTIFICATION DIVISION.
       PROGRAM-ID. REPLAY.
       AUTHOR. JOHN CHIRPICH.
       DATE-WRITTEN. 11-16-24.
       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
       SELECT FC-REPLAY-FILE ASSIGN TO './live.replay'
                   ORGANIZATION IS INDEXED
                   ACCESS MODE IS DYNAMIC
                   RECORD KEY IS FS-REPLAY-TURN-NUM.
       DATA DIVISION.
       FILE SECTION.
       FD FC-REPLAY-FILE.
       01 FS-REPLAY.
           02 FS-REPLAY-TURN-NUM PIC 999.
           02 FS-REPLAY-X PIC S99.
           02 FS-REPLAY-Y PIC S99.
           02 FS-REPLAY-PIECE PIC 9.
           02 FS-REPLAY-PLAYER PIC 9.
       WORKING-STORAGE SECTION.
      * 01 WS-REPLAY.
       01 WS-REPLAY-TURN-NUM PIC 999.
      *     02 WS-REPLAY-X PIC S99.
      *     02 WS-REPLAY-Y PIC S99.
      *    02 WS-REPLAY-PIECE PIC 9.
      *    02 WS-REPLAY-PLAYER PIC 9.
      *    02 WS-REPLAY-PLAYED PIC 9.
       LINKAGE SECTION.
       01 LS-TURN-NUM USAGE BINARY-LONG.
       01 LS-REPLAY-X USAGE BINARY-LONG.
       01 LS-REPLAY-Y USAGE BINARY-LONG.
       01 LS-REPLAY-PIECE USAGE BINARY-LONG.
       01 LS-REPLAY-PLAYER USAGE BINARY-LONG.
       PROCEDURE DIVISION. 
       main.
           ENTRY "replay" USING BY REFERENCE LS-TURN-NUM
           DISPLAY LS-TURN-NUM
           move 5 to LS-TURN-NUM
           DISPLAY LS-TURN-NUM
           GOBACK. 
       second.
           entry "replay2" using BY REFERENCE LS-TURN-NUM
           move 6 to LS-TURN-NUM
           GOBACK.
       100-ADD-ENTRY.
           entry "addtofile" USING BY REFERENCE LS-TURN-NUM
                                BY REFERENCE LS-REPLAY-X
                                BY REFERENCE LS-REPLAY-Y
                                BY REFERENCE LS-REPLAY-PIECE
                                BY REFERENCE LS-REPLAY-PLAYER
           OPEN I-O FC-REPLAY-FILE
           MOVE LS-TURN-NUM TO FS-REPLAY-TURN-NUM
           MOVE LS-REPLAY-X TO FS-REPLAY-X
           MOVE LS-REPLAY-Y TO FS-REPLAY-Y
           MOVE LS-REPLAY-PIECE TO FS-REPLAY-PIECE
           MOVE LS-REPLAY-PLAYER TO FS-REPLAY-PLAYER
           WRITE FS-REPLAY
           END-WRITE
           CLOSE FC-REPLAY-FILE
           GOBACK.
       110-GET-ENTRY.
           ENTRY "retrieveReplay" USING BY REFERENCE LS-TURN-NUM
                                BY REFERENCE LS-REPLAY-X
                                BY REFERENCE LS-REPLAY-Y
                                BY REFERENCE LS-REPLAY-PIECE
                                BY REFERENCE LS-REPLAY-PLAYER
           MOVE LS-TURN-NUM TO FS-REPLAY-TURN-NUM
           OPEN I-O FC-REPLAY-FILE
           START FC-REPLAY-FILE KEY IS EQUAL TO FS-REPLAY-TURN-NUM 
                INVALID KEY
                        MOVE -1 TO LS-REPLAY-X 
                        MOVE -1 TO LS-REPLAY-Y
                NOT INVALID KEY
                        READ FC-REPLAY-FILE
                        MOVE FS-REPLAY-TURN-NUM TO LS-TURN-NUM
                        MOVE FS-REPLAY-X TO LS-REPLAY-X
                        MOVE FS-REPLAY-Y TO LS-REPLAY-Y
                        MOVE FS-REPLAY-PIECE TO LS-REPLAY-PIECE
                        MOVE FS-REPLAY-PLAYER TO LS-REPLAY-PLAYER
           END-START
           CLOSE FC-REPLAY-FILE
           GOBACK.
       120-CREATE-FILE.
           ENTRY "createFile"
           OPEN OUTPUT FC-REPLAY-FILE
           CLOSE FC-REPLAY-FILE
           GOBACK.
