#include "../header/functions.h"

char mode_start;
char movement;

void write_in_queue(RT_QUEUE *, Message);

void envoyer(void * arg) {
    int err;
    Message msg;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);

    while (1) {
#ifdef _WITH_TRACE_
        printf("%s : waiting for a message in queue\n", info.name);
#endif
        if (rt_queue_read(&queueMsgGUI, &msg, sizeof (Message), TM_INFINITE) >= 0) {
#ifdef _WITH_TRACE_
            printf("%s : message {%s,%s} in queue\n", info.name, msg.header, msg.data);
#endif
            send_message_to_monitor(msg.header, msg.data);
            rt_queue_free(&queueMsgGUI, &msg);
        } else {
            printf("Error msg queue write: %s\n", strerror(-err));
        }
    }
}

void connecter(void * arg) {
    int err;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);

    while (1) {
#ifdef _WITH_TRACE_
        printf("%s : Wait semConnecterRobot\n", info.name);
#endif
        rt_sem_p(&semConnecterRobot, TM_INFINITE);
#ifdef _WITH_TRACE_
        printf("%s : semConnecterRobot arrived => Start robot\n", info.name);
#endif
        if (mode_start == 'u') { // start without watchdog
            err = send_command_to_robot(DMB_START_WITHOUT_WD);
        } else {// start with watchdog
            err = send_command_to_robot(DMB_START_WITH_WD);
        }
        if (err == 0) {
#ifdef _WITH_TRACE_
            printf("%s : the robot is started\n", info.name);
#endif
            Message msg;
            memcpy(&msg.header, HEADER_STM_ACK, sizeof (HEADER_STM_ACK));
            write_in_queue(&queueMsgGUI, msg);
        }
    }
}

void communiquer(void *arg) {
    Message msg;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    do {
        receive_message_from_monitor(msg.header, msg.data);
#ifdef _WITH_TRACE_
        printf("%s: msg {header:%s,data=%s} received from UI\n", info.name, msg.header, msg.data);
#endif
        if (strcmp(msg.header, HEADER_MTS_DMB_ORDER) == 0) {
            if (msg.data[0] == 'c') { // Open communication supervisor-robot
#ifdef _WITH_TRACE_
                printf("%s: try to open Xbee communication\n", info.name);
#endif
                if (open_communication_robot() < 0) {
#ifdef _WITH_TRACE_
                    printf("%s: Xbee communication failed\n", info.name);
#endif
                    Message msg;
                    memcpy(&msg.header, HEADER_STM_ACK, sizeof (HEADER_STM_ACK));
                    write_in_queue(&queueMsgGUI, msg);
                } else {
#ifdef _WITH_TRACE_
                    printf("%s: Xbee communication available\n", info.name);
#endif
                    Message msg;
                    memcpy(&msg.header, HEADER_STM_ACK, sizeof (HEADER_STM_ACK));
                    write_in_queue(&queueMsgGUI, msg);
                }
            } else if ((msg.data[0] == 'u') || (msg.data[0] == 'w')) {
                mode_start = msg.data[0];
                rt_sem_v(&semConnecterRobot);
            } else if ((msg.data[0] == 'F')
                    || (msg.data[0] == 'B')
                    || (msg.data[0] == 'L')
                    || (msg.data[0] == 'R')
                    || (msg.data[0] == 'S')) {
                movement = msg.data[0];
#ifdef _WITH_TRACE_
                printf("%s: update movement with %c\n", info.name, movement);
#endif

            }
        } else if (strcmp(msg.header, HEADER_MTS_MSG) == 0) {

        }
    } while ((strcmp(msg.header, HEADER_MTS_MSG) != 0) || (msg.data[0] != 'C'));

}

void deplacer(void *arg) {
    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);

    /* PERIODIC START */
#ifdef _WITH_TRACE_
    printf("%s: start period\n", info.name);
#endif
    rt_task_set_periodic(NULL, TM_NOW, 1000000000);
    while (1) {
#ifdef _WITH_TRACE_
        printf("%s: Wait period \n", info.name);
#endif
        rt_task_wait_period(NULL);
#ifdef _WITH_TRACE_
        printf("%s: Periodic activation\n", info.name);
        printf("%s: send movement %c to the robot\n", info.name, movement);
#endif
        if (send_command_to_robot(movement) >= 0) {
#ifdef _WITH_TRACE_
            printf("%s: the movement %c was successfully received\n", info.name, movement);
#endif            
        } else {
#ifdef _WITH_TRACE_
            printf("%s: the movement %c was unsuccessful received\n", info.name, movement);
#endif  
        }
    }
}

void write_in_queue(RT_QUEUE *queue, Message msg) {
    void *buff;
    buff = rt_queue_alloc(&queueMsgGUI, sizeof (Message));
    memcpy(buff, &msg, sizeof (Message));
    rt_queue_send(&queueMsgGUI, buff, sizeof (Message), Q_NORMAL);
}