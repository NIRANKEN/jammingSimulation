#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias diff='diff --color=auto'
alias ll='ls -la'
alias tmux='tmux -2'

#GTK_IM_MODULE=fcitx
#QT_IM_MODULE=fcitx
#XMODIFIERS=@im=fcitx

PS1='[\u@\h \W]\$ '
