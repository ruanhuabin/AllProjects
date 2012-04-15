" File: SingleCompile.vim
" Version: 0.1.2
" Author: Hong Xu(xuphys AT gmail DOT com)
" Last Change: 6 June 2010
" Description: Let user compile or run a single source file conveniently.
" License: You can redistribute this plugin and / or modify it under the terms 
"          of the GNU General Public License as published by the Free Software 
"          Foundation; either version 2, or any later version. 

if v:version < 700
    finish
endif

" check whether this script is already loaded
if exists("g:loaded_SingleCompile")
    finish
endif
let g:loaded_SingleCompile = 1

let s:saved_cpo = &cpo
set cpo&vim

let g:SingleCompile_version = 1

" default options {{{
if !exists('g:SingleCompile_autowrite')
    let g:SingleCompile_autowrite=1
endif
" }}}

" templates {{{
let g:SingleCompile_templates={}
" c
let g:SingleCompile_templates['c']={}
let g:SingleCompile_templates['c']['command']='cc'
let g:SingleCompile_templates['c']['flags']='-o %<'
let g:SingleCompile_templates['c']['run']='./%<'
" cpp
let g:SingleCompile_templates['cpp']={}
let g:SingleCompile_templates['cpp']['command']='g++'
let g:SingleCompile_templates['cpp']['flags']=g:SingleCompile_templates['c']['flags']
let g:SingleCompile_templates['cpp']['run']=g:SingleCompile_templates['c']['run']
" java
let g:SingleCompile_templates['java']={}
let g:SingleCompile_templates['java']['command']='javac'
let g:SingleCompile_templates['java']['flags']=''
let g:SingleCompile_templates['java']['run']='java %<'
" shell
let g:SingleCompile_templates['sh']={}
let g:SingleCompile_templates['sh']['command']='sh'
let g:SingleCompile_templates['sh']['flags']=''
let g:SingleCompile_templates['sh']['run']=''
" batch
let g:SingleCompile_templates['dosbatch']={}
let g:SingleCompile_templates['dosbatch']['command']=''
let g:SingleCompile_templates['dosbatch']['flags']=''
let g:SingleCompile_templates['dosbatch']['run']=''

" }}}

" functions {{{
function s:Compile()
    if !has_key(g:SingleCompile_templates,&filetype)
        echo 'Your file type is not supported!'
        return
    endif
    
    " switch current work directory to the file's directory
   " let l:curcwd=getcwd()
    "cd %:p:h

    if g:SingleCompile_autowrite != 0
        exec 'w'
    endif
	
	
    let l:compile_cmd = g:SingleCompile_templates[&filetype]['command']
    let l:compile_flags = g:SingleCompile_templates[&filetype]['flags']

	exec '!echo -n "========================="'
	exec '!date'
	exec '!echo "========================"'
    exec '!'.l:compile_cmd.' '.l:compile_flags.' %:p'

    " switch back to the original directory
    "exec 'cd '.l:curcwd
	exec '! read ans'
    return
endfunction

function s:Run()
    if !has_key(g:SingleCompile_templates,&filetype)
        return
    endif

    "let l:curcwd=getcwd()
    "cd %:p:h

    let l:run_cmd=g:SingleCompile_templates[&filetype]['run']

    exec '!'.l:run_cmd

   " exec 'cd '.l:curcwd

    return
endfunction

function s:CompileRun()
    call s:Compile()
    call s:Run()
endfunction

" }}}

" command {{{
command SingleCompile       call s:Compile()
command SingleCompileRun    call s:CompileRun()
" }}}

let &cpo = s:saved_cpo

" vim:fdm=marker
