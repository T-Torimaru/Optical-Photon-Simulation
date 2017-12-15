#
# Example .zshrc file for zsh 4.0
#
# .zshrc is sourced in interactive shells.  It
# should contain commands to set up aliases, functions,
# options, key bindings, etc.
#


# THIS FILE IS NOT INTENDED TO BE USED AS /etc/zshrc, NOR WITHOUT EDITING
#return 0	# Remove this line after editing this file as appropriate

# Search path for the cd command
cdpath=(.. ~ ~/src ~/zsh)

# Use hard limits, except for a smaller stack and no core dumps
#unlimit
#limit stack 8192
#limit core 0
#limit -s

umask 022

# Set up aliases
alias vim='/usr/bin/vim -X'
alias mv='nocorrect mv'       # no spelling correction on mv
alias cp='nocorrect cp'       # no spelling correction on cp
alias mkdir='nocorrect mkdir' # no spelling correction on mkdir
alias j=jobs
alias pu=pushd
alias po=popd
alias d='dirs -v'
alias h=history
alias grep='egrep -i'
alias ls='ls -F --color=auto'
alias ll='ls -l'
alias la='ls -a'
alias gd='dirs -v; echo -n "select number: "; read newdir; cd -"$newdir"'
alias w3m='w3m http://www.icepp.s.u-tokyo.ac.jp/~wataru'
alias w3mggl='w3m http://www.google.co.jp'
alias acroread='/usr/local/Acrobat4/bin/acroread'
alias a2ps='a2ps-j'
alias up='cd ..'
alias rm='rm -i'
alias eterm='Eterm -O --tarns'
alias view='/usr/bin/vim -R'
alias ctags='ctags -R --langmap=Fortran:+.inc --exclude=meg.check'
#alias emacs='emacs -nw'

alias ssh='ssh -X'

#alias root='/afs/psi.ch/user/o/ootani/cern/root/bin/root'
# List only directories and symbolic
# links that point to directories
alias lsd='ls -ld *(-/DN)'

# List only file beginning with "."
alias lsa='ls -ld .*'

# MEG MC checkout
alias megsvnco='svn co svn+ssh://ootani@savannah.psi.ch/afs/psi.ch/project/meg/svn/meg/trunk/megmc megmc'

# Shell functions
setenv() { typeset -x "${1}${1:+=}${(@)argv[2,$#]}" }  # csh compatibility
freload() { while (( $# )); do; unfunction $1; autoload -U $1; shift; done }

# Where to look for autoloaded function definitions
fpath=($fpath ~/.zfunc)

# Autoload all shell functions from all directories in $fpath (following
# symlinks) that have the executable bit on (the executable bit is not
# necessary, but gives you an easy way to stop the autoloading of a
# particular shell function). $fpath should not be empty for this to work.
for func in $^fpath/*(N-.x:t); autoload $func

# automatically remove duplicates from these arrays
typeset -U path cdpath fpath manpath

# Global aliases -- These do not have to be
# at the beginning of the command line.
alias -g M='|more'
alias -g H='|head'
alias -g T='|tail'

manpath=(    
        /usr/share/man
        /usr/X11R6/man
        /usr/local/man
        /usr/kerberos/man
        /usr/lib/perl5/man
        /usr/man
        /usr/man/ja_JP.ujis
        /usr/man
        /usr/local/man
        /usr/X11R6/man/ja_JP.EUC
        /usr/man/ja_JP.EUC
        /usr/X11R6/man
        /usr/lib/perl5/man
#       /usr/openwin/man
        /usr/local/pgsql/man
        /usr/X11R6/lib/X11/xqscan
        /usr/pilot/man
        /usr/local/lib/stk/man
	/usr/extra/pilot-head/man
        )
export MANPATH


#Language
export LANG='en_US.UTF-8'

# Hosts to use for completion (see later zstyle)
hosts=(`hostname` ftp.math.gatech.edu prep.ai.mit.edu wuarchive.wustl.edu)

# Set prompts
PROMPT="%B$USER@%m%#%b "    # default prompt
RPROMPT="[%~]"
# Some environment variables
export MAIL=/var/spool/mail/$USERNAME
export HELPDIR=/usr/local/lib/zsh/help  # directory for run-help function to find docs
export EDITOR="/usr/bin/vim"

####export ROOTSYS=/cern/root
#export ROOTSYS=/home/scratch/ootani/opt/root
export ROOTSYS=/cern/root

# MEG Software
#export MEGSYS=/net/megmac00/Volumes/megraid0/nfs/users/wataru/MEGSoftware/meg2
export MEGSYS=/net/megsrv00/megpv00/nfs/users/wataru/MEGSoftware/meg
export MEG2SYS=/net/megsrv00/megpv00/nfs/users/wataru/MEGSoftware/meg2
#export ROMESYS=/net/megmac00/Volumes/megraid0/nfs/users/wataru/MEGSoftware/rome
export ROMESYS=/net/megsrv00/megpv00/nfs/users/wataru/MEGSoftware/rome
#export MIDAS_ROOT=/net/megmac00/Volumes/megraid0/nfs/users/wataru/MEGSoftware/midas
export MIDAS_ROOT=/net/megsrv00/megpv00/nfs/users/wataru/MEGSoftware/midas
#export MIDAS_DIR=/net/megmac00/Volumes/megraid0/nfs/users/wataru/MEGSoftware/midas
export MIDAS_DIR=/net/megsrv00/megpv00/nfs/users/wataru/MEGSoftware/midas
# environment for CVS and Subversion
#export CVSROOT=$HOME/CVS_DB
export CVSROOT=":ext:ootani@midas.psi.ch:/usr/local/cvsroot"
#export CVSROOT=":ext:meg@midas.psi.ch:/usr/local/cvsroot"
export CVS_RSH="ssh"
#export MEG_DIR="/scratch1/wataru/MEGsim/meg"
#export MEG_DIR="/scratch/wataru/MEGsim/meg"
export MEG_DIR=$MEGSYS/megmc
export CVSEDITOR="/usr/bin/vim"
export SVN_EDITOR="/usr/bin/vim"
export RULESSRC=$MEG_DIR/Rules
export PROJRULES=$MEG_DIR/MegRules

export CERN="/cern"
#export CERN_LEVEL="pro"
export CERN_LEVEL="2005"
#export GEANT=${CERN}/${CERN_LEVEL}/lib
export GEANT=geant321
#export GEANT_LIBS=${CERN}/${CERN_LEVEL}/lib
#export GEANT_INC=${CERN}/${CERN_LEVEL}/include

export INSTDIR=/afs/psi.ch/project/meg/www/subprojects/install

export SPXSYS=$MEGSYS/../spx


# MEG GEM
#export MEGMC=/scratch/ootani/MEGsim/megmc
export MEGMC=/scratch1/ootani/MEGsim/megmc

export lpuserflags="-Wall -g -O2" 

MAILCHECK=300
HISTSIZE=200
DIRSTACKSIZE=20

# Watch for my friends
#watch=( $(<~/.friends) )       # watch for people in .friends file
watch=(notme)                   # watch for everybody but me
LOGCHECK=300                    # check every 5 min for login/logout activity
WATCHFMT='%n %a %l from %m at %t.'

# Set/unset  shell options
setopt   notify globdots correct pushdtohome cdablevars autolist
#setopt   correctall autocd recexact longlistjobs
setopt   correctall recexact longlistjobs
setopt   autoresume histignoredups pushdsilent noclobber pushdignoredups
setopt   autopushd pushdminus extendedglob rcquotes mailwarning
#unsetopt bgnice autoparamslash
setopt EXTENDED_GLOB
setopt AUTO_CD
setopt AUTO_LIST
setopt AUTO_MENU
setopt AUTO_PARAM_SLASH
setopt CHASE_LINKS
setopt HIST_IGNORE_SPACE
setopt autocd


# Autoload zsh modules when they are referenced
zmodload -a zsh/stat stat
zmodload -a zsh/zpty zpty
zmodload -a zsh/zprof zprof
zmodload -ap zsh/mapfile mapfile

# Some nice key bindings
#bindkey '^X^Z' universal-argument ' ' magic-space
#bindkey '^X^A' vi-find-prev-char-skip
#bindkey '^Xa' _expand_alias
#bindkey '^Z' accept-and-hold
#bindkey -s '€M-/' €€€€
#bindkey -s '€M-=' €|

# bindkey -v               # vi key bindings

bindkey -e                 # emacs key bindings
bindkey ' ' magic-space    # also do history expansion on space
bindkey '^I' complete-word # complete on tab, leave expansion to _expand

# Setup new style completion system. To see examples of the old style (compctl
# based) programmable completion, check Misc/compctl-examples in the zsh
# distribution.
autoload -U compinit
compinit

# Completion Styles

# list of completers to use
zstyle ':completion:*::::' completer _expand _complete _ignored _approximate

# allow one error for every three characters typed in approximate completer
#zstyle -e ':completion:*:approximate:*' max-errors€ 
#    'reply=( $(( ($#PREFIX+$#SUFFIX)/3 )) numeric )'

# insert all expansions for expand completer
zstyle ':completion:*:expand:*' tag-order all-expansions

# formatting and messages
zstyle ':completion:*' verbose yes
zstyle ':completion:*:descriptions' format '%B%d%b'
zstyle ':completion:*:messages' format '%d'
zstyle ':completion:*:warnings' format 'No matches for: %d'
zstyle ':completion:*:corrections' format '%B%d (errors: %e)%b'
zstyle ':completion:*' group-name ''

# match uppercase from lowercase
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'

# offer indexes before parameters in subscripts
zstyle ':completion:*:*:-subscript-:*' tag-order indexes parameters

# command for process lists, the local web server details and host completion
#zstyle ':completion:*:processes' command 'ps -o pid,s,nice,stime,args'
#zstyle ':completion:*:urls' local 'www' '/var/www/htdocs' 'public_html'
zstyle '*' hosts $hosts

# Filename suffixes to ignore during completion (except after rm command)
#zstyle ':completion:*:*:(^rm):*:*files' ignored-patterns '*?.o' '*?.c~' €
#    '*?.old' '*?.pro'
# the same for old style completion
#fignore=(.o .c~ .old .pro)

# ignore completion functions (until the _ignored completer)
zstyle ':completion:*:functions' ignored-patterns '_*'

#eval `dircolors`
#zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}

## #from .zshenv 
export LS_COLORS='*.pdf=32:*.png=01;35:*.JPG=00;35:*.jpg=00;35:di=01;36:ln=04;36'

#export DISPLAY=umemaru.psi.ch:0.0

###export QTDIR=/scratch1/ootani/opt/qt
###export QTINC=${QTDIR}/include
###export QTLIB=${QTDIR}/lib
#export ROOTSYS=/afs/psi.ch/user/o/ootani/cern/root
export DYLD_LIBRARY_PATH=${ROOTSYS}/lib
export LD_LIBRARY_PATH=${ROOTSYS}/lib:/usr/local/lib:${QTDIR}/lib:${MEGSYS}/gem4
# Some environment variables
export MAIL=/var/spool/mail/$USERNAME
export LESS=-cx3M
export HELPDIR=/usr/local/lib/zsh/help  # directory for run-help function to find docs


path=(. ${HOME}/bin /bin ${QTDIR}/bin /usr/bin /usr/local/bin ${HOME}/private/bin 
/usr/X11R6/bin /cern/pro/bin ${ROOTSYS}/bin 
/sbin /usr/sbin /usr/extra/pilot-head/bin
/usr/local/netscape ${HOME}/perl 
/Developer/Tools ${ROMESYS}/bin) 

### Environments for GEANT4

 export G4WORKDIR=${MEGSYS}/gem4
 export G4SYSTEM=Linux-g++ 
# export G4INSTALL=/usr/local/geant4.6.0.p01 
 export G4INSTALL=/usr/local/geant4
 export CLHEP_BASE_DIR=/usr/local/CLHEP 
 export CLHEP_INCLUDE_DIR=/usr/local/include/CLHEP 
 export CLHEP_LIB_DIR=/usr/local/lib 
 export CLHEP_LIB=CLHEP-g++ 
 export G4USE_STL=1 


 export G4USE_STLPORT=1 
 export STLORTDIR=/usr/local/STLport-4.5.3 

 export G4LEDATA=$G4INSTALL/data/G4EMLOW2.3 
 export G4LEVELGAMMADATA=$G4INSTALL/data/PhotonEvaporation 
 export NeutronHPCrossSections=$G4INSTALL/data/G4NDL3.7 
 export G4RADIOACTIVEDATA=$G4INSTALL/data/RadiativeDecay 




 export G4DAWNFILE_VIEWER="dawn -d" 

 export G4VIS_BUILD_DAWN_DRIVER=1 
 export G4VIS_BUILD_DAWNFILE_DRIVER=1 
 export G4VIS_USE_DAWN=1 
 export G4VIS_USE_DAWNFILE=1 

 export OPENGL_INSTALLED=1 
 export G4VIS_BUILD_OPENGLX_DRIVER=1 
 export G4VIS_USE_OPENGLX=1 
 export OGLHOME=/usr/X11R6/ 

 export TCL_LIBRARY=/usr/lib/tcl
 export TK_LIBRARY=/usr/lib/tk


# export G4WORKDIR=$HOME/geant4
# export G4BIN=$HOME/geant4/bin
# export G4TMP=$HOME/geant4/tmp
 export G4BIN=${G4WORKDIR}/bin
 export G4TMP=${G4WORKDIR}/tmp


export WORDCHARS='*?_-.[]~=&;!#$%^(){}<>'

#bindkey '^P' history-beginning-search-backward
#bindkey '^N' history-beginning-search-forward
autoload history-search-end
zle -N history-beginning-search-backward-end history-search-end
zle -N history-beginning-search-forward-end history-search-end
bindkey "^P" history-beginning-search-backward-end
bindkey "^N" history-beginning-search-forward-end

#Geant4 setup (MEG)
source /cern/geant4/src/geant4/env.sh


# functions
function psg() {
ps -aux | head -n 1		
ps -aux | grep $* | grep -v "ps -auxww" | grep -v grep 
}

function euc() {     
    for i in $@; do;
	nkf -e -Lu $i >! /tmp/euc.$$ 
	mv -f /tmp/euc.$$ $i
    done;
}

function sjis() {
for i in $@; do;
    nkf -s -Lw $i >! /tmp/euc.$$ 
    mv -f /tmp/euc.$$ $i
done;
}

#### history
HISTFILE="$HOME/.zhistory"
HISTSIZE=10000
SAVEHIST=10000

#### option, limit, bindkey
setopt  hist_ignore_all_dups
setopt  hist_reduce_blanks 
setopt  share_history 
setopt HIST_IGNORE_SPACE
bindkey -e
bindkey "^?"    backward-delete-char
bindkey "^H"    backward-delete-char
bindkey "^[[3~" delete-char
bindkey "^[[1~" beginning-of-line
bindkey "^[[4~" end-of-line


alias -g L="| less"
alias -g M="| less"
alias -g G='| grep'
alias -g C='| cat -n'
alias -g W='| wc'
alias -g H='| head'
alias -g T='| tail'
alias -g ....='../..'

# distcc
#export DISTCC_HOSTS="localhost/1 ucipsi1/2 megonln02/1 megsc01/1 megterm01/1 bahamoud/1 pc4466/1 pc4465/1"
#export DISTCC_HOSTS="localhost/1 megofl00/1  megofl01/1  megofl02/1  megofl03/1  megofl04/1" 
export DISTCC_HOSTS="localhost/1 megofl00/1  megofl01/1  megofl03/1  megofl04/5" 
###export CC="distcc -m64"
###export CXX="distcc -m64"
export JOBSFLAG="-j10"
#

export CC="gcc -m64"
export CXX="g++ -m64"


###export DISTCC_HOSTS="localhost/1 ucipsi1/2"
###export CC="gcc"
###export CXX="g++"
###export JOBSFLAG="-j3"


###export CXX="distcc x86_64-redhat-linux-g++ -m32 -I/usr/include"
###export CC="distcc x86_64-redhat-linux-gcc -m32 -I/usr/include"
###export CXXLD="g++"
###export JOBSFLAG="-j9"

