#!/bin/bash
# Project 2 - Advanced System Monitoring Script (with proper stop)
LOGFILE="$HOME/sysmonitor.log"
CONFIGFILE="$HOME/.sysmonitor.conf"
PIDFILE="$HOME/.sysmonitor.pid"

# Default thresholds
CPU_THRESH=80
MEM_THRESH=80
DISK_THRESH=90
INTERVAL=60

# Load config
[ -f "$CONFIGFILE" ] && source "$CONFIGFILE"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a "$LOGFILE"
}

get_cpu() { top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}'; }
get_mem() { free -m | awk '/Mem/{printf "%.1f", $3/$2*100}'; }
get_disk() { df ~ | awk 'NR==2 {print substr($5,1,length($5)-1)}'; }

show_status() {
    clear
    echo "=== System Status ==="
    printf "CPU Usage : %.1f%%\n" $(get_cpu)
    printf "Memory    : %.1f%%\n" $(get_mem)
    printf "Disk (~)  : %s%%\n" $(get_disk)
    echo "Log file  : $LOGFILE"
    [ -f "$PIDFILE" ] && echo "Monitoring: RUNNING (PID: $(cat $PIDFILE))"
    [ ! -f "$PIDFILE" ] && echo "Monitoring: Stopped"
    echo
}

monitor_loop() {
    echo $$ > "$PIDFILE"
    while true; do
        CPU=$(get_cpu)
        MEM=$(get_mem)
        DISK=$(get_disk)

        (( $(echo "$CPU > $CPU_THRESH" | bc -l) )) && log "ALERT: CPU High (${CPU}% > ${CPU_THRESH}%)"
        (( $(echo "$MEM > $MEM_THRESH" | bc -l) )) && log "ALERT: Memory High (${MEM}% > ${MEM_THRESH}%)"
        (( DISK > DISK_THRESH )) && log "ALERT: Disk Full (${DISK}% > ${DISK_THRESH}%)"

        sleep $INTERVAL
    done
}

start_monitoring() {
    if [ -f "$PIDFILE" ]; then
        echo "Monitoring already running (PID: $(cat $PIDFILE))"
    else
        monitor_loop &
        log "Monitoring started in background (PID: $!)"
        echo "Monitoring started (PID: $!)"
    fi
}

stop_monitoring() {
    if [ -f "$PIDFILE" ]; then
        kill $(cat "$PIDFILE") 2>/dev/null && rm "$PIDFILE"
        log "Monitoring stopped by user"
        echo "Monitoring stopped."
    else
        echo "No monitoring process is running."
    fi
}

# ... (set_thresholds, etc. same as before)

menu() {
    while true; do
        show_status
        echo "1. View Status"
        echo "2. Set Thresholds"
        echo "3. View Log"
        echo "4. Clear Log"
        echo "5. Start Monitoring (background)"
        echo "6. Stop Monitoring"          # ← NEW OPTION
        echo "7. Exit"
        read -p "Choose: " choice
        case $choice in
            1) show_status; read -p "Press Enter..." ;;
            2) set_thresholds ;;
            3) less "$LOGFILE" 2>/dev/null || echo "Log empty" ;;
            4) : > "$LOGFILE"; log "Log cleared" ;;
            5) start_monitoring ;;
            6) stop_monitoring ;;
            7) stop_monitoring; echo "Goodbye!"; exit 0 ;;
            *) echo "Invalid option" ;;
        esac
    done
}

touch "$LOGFILE"
log "System monitor started by $USER"
menu
