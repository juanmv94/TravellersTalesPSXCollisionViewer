//////////////////
// PASTE THIS CODE ON CHEAT ENGINE AUTO ASSEMBLE AT MAIN MENU
// START ANY LEVEL (ACTIVE CAMERA) WITH RECORD DATA AT 0X55B000.
////////////


//Injected code
label(difcomb)

0055AF00:
mov ecx,[55aff0] //get key combination counter
mov eax,[ecx*4+55b000] //get current pair
or [0052AD88],ax //add path keys to input
or [0088279C],ax //fix needed for dialogs
rol eax,10 //rotate combination counter to ax
cmp [55aff4],ax
je difcomb
inc [55aff4]
ret
difcomb:
inc ecx
mov [55aff0],ecx
mov [55aff4],0000
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
