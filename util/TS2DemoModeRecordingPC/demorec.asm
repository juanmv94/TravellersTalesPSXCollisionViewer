// PC demo path recording for TS2 (Cheat Engine Auto Assembler)
// Start any level from savegame (use active camera)
// or just wait for demo mode levels to start
// Play the level and finish the recording at any moment with pause key
// A new file yourpath.bin will be created on your game directory
// You can replace paths from PAD directory with your generated ones


/////////
// Code injection and demo path array
// on empty memory areas from 0x55AE00
///////
label(difcomb)
label(cleardata)
label(endsave)

0055AE00: //save, and return current keyboard input in dx
mov ecx,[55aff0] //get key combination counter
mov edx,[ecx*4+55affc] //get current pair
cmp [00529B00],dx //same combination?
jne difcomb
add edx,0x10000 //increment frames
mov [ecx*4+55affc],edx //update frames
ret
difcomb:
inc ecx //increment combination counter
mov [55aff0],ecx
mov dx,[00529B00] //set new key combination
mov [ecx*4+55affc],dx
ret

0055AF00: //export generated path to file
cmp [55aff0],00000000
je endsave
//Append 00 00 ff ff at the end of recording
inc [55aff0]
mov eax,[55aff0]
mov [eax*4+55affc],ffff0000
//TS2 routine to open file in write mode
push 000001a4
push 00000040
push 00008301
push 0055AFE0 //name of file
call 004D670B //fd -> eax
add esp,10
mov [55aff4],eax
//TS2 routine to write data
mov eax,[55aff0] //get number of combinations
sal eax,2 //size=combinations*4
push eax //size of data
push 0055B000 //data address
push [55aff4] //fd
call 004D3A95
add esp,0C
//TS2 routine to close file
push [55aff4] //fd
call 004D307F
add esp,04
mov eax,[55aff0]
cleardata:
mov [eax*4+0055AFFC],00000000
dec eax
jne cleardata
mov [55aff0],00000000
endsave:
mov [0052AD94],01 //set demo mode flag for next rec
ret

0055AFE0: //name of the saved file
db 'yourpath.bin', 0

//Start of recording array (after these 4 bytes)
0055AFFC:
db ff ff ff ff

/////////
// Points of injection
///////

0049E0C0: //Point of injection replacing next demo key input
call 0055AE00
nop
nop
nop

00453C6D: //Point of injection saving path after level/menu load
jmp 0055AF00

/////////
// Other fixes
///////

//Don't increase demo file playback counter
0049E0B2:
mov al,02
nop

//Don't end demo when key press
0049DFE0:
mov dx,0000
nop
nop
nop
