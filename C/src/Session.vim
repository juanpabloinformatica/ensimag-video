let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Documents/ensimag/sem_7/ensimag-video/C/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +143 stream_common.c
badd +16 ensitheora.h
badd +49 ensitheora.c
badd +43 synchro.h
badd +83 synchro.c
argglobal
%argdel
$argadd .
edit ensitheora.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 70 + 106) / 212)
exe 'vert 2resize ' . ((&columns * 70 + 106) / 212)
exe 'vert 3resize ' . ((&columns * 70 + 106) / 212)
argglobal
balt ensitheora.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 57 - ((34 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 016|
lcd ~/Documents/ensimag/sem_7/ensimag-video/C/src
wincmd w
argglobal
if bufexists(fnamemodify("~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.c", ":p")) | buffer ~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.c | else | edit ~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.c | endif
if &buftype ==# 'terminal'
  silent file ~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.c
endif
balt ~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 126 - ((21 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 126
normal! 05|
lcd ~/Documents/ensimag/sem_7/ensimag-video/C/src
wincmd w
argglobal
if bufexists(fnamemodify("~/Documents/ensimag/sem_7/ensimag-video/C/src/synchro.c", ":p")) | buffer ~/Documents/ensimag/sem_7/ensimag-video/C/src/synchro.c | else | edit ~/Documents/ensimag/sem_7/ensimag-video/C/src/synchro.c | endif
if &buftype ==# 'terminal'
  silent file ~/Documents/ensimag/sem_7/ensimag-video/C/src/synchro.c
endif
balt ~/Documents/ensimag/sem_7/ensimag-video/C/src/ensitheora.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
24,24fold
25,25fold
26,26fold
28,45fold
46,59fold
let &fdl = &fdl
24
normal! zo
25
normal! zo
let s:l = 84 - ((22 * winheight(0) + 20) / 41)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 84
normal! 0
lcd ~/Documents/ensimag/sem_7/ensimag-video/C/src
wincmd w
3wincmd w
exe 'vert 1resize ' . ((&columns * 70 + 106) / 212)
exe 'vert 2resize ' . ((&columns * 70 + 106) / 212)
exe 'vert 3resize ' . ((&columns * 70 + 106) / 212)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
