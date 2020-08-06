//////////////////
// PASTE THIS CODE ON CHEAT ENGINE AUTO ASSEMBLE AT MAIN MENU
// START ANY LEVEL (ACTIVE CAMERA) AND RECORD DATA WILL BE
// RECORDED FROM 0X55B000. PAUSING GAME STOPS THE RECORDING.
// WHEN PAUSED, COPY GENERATED DATA UP TO 08 00 00 00 TO FILE
////////////


//Injected code
label(difcomb)

0055AF00:
mov ecx,[55aff0] //get key combination counter
mov eax,[ecx*4+55b000] //get current pair
cmp [0052AD88],ax //same combination?
jne difcomb
add eax,0x10000 //increment frames
mov [ecx*4+55b000],eax //update frames
ret
difcomb:
inc ecx
mov [55aff0],ecx
mov ax,[0052AD88]
mov [ecx*4+55b000],ax
ret

//Point of injection just after reading ongame key input
0049EBFA:
call 0055AF00
ret

//disable dynamic speed multiplier
004908C3:
db 90 90 90 90 90 90
004908EE:
db 90 90 90 90 90 90
00453D42:
db 90 90 90 90 90 90 90 90 90 90
00438D67:
db 90 90 90 90 90 90
00490918:
db 90 90 90 90 90 90
0049095A:
db 90 90 90 90 90 90
0049DC2D:
db 90 90 90 90 90 90
004399D3:
db 90 90 90 90 90 90
00437C95:
db 90 90 90 90 90 90 90 90 90 90

0052f2d4:
db 02
