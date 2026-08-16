#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 256
#define MAX_NAME 64

void print_banner() {
    printf("            .-=+**+=:                                                                                                      \n");
    printf(" .       :=-...       ..==.                                                                                                 \n");
    printf("   .  .=:                 .--                                                                                               \n");
    printf("    :.:.....                .::          :@@@@@@@@@@@@@@@#                                   @@@@: :@@@@               @@@@.\n");
    printf("   .-::==:::.::::.            .=         *@@@@@@@@@@@@@@@@@-                                 @@@@# .@@@@.              @@@@-\n");
    printf("  .-. :====-::..:..-::.        .=        *@@@@        -@@@@@        -*##=             =#*-   @@@@# .@@@@.  :+%%*.            \n");
    printf("  =.  -+++=-:-:-:.:-.:=-.       .=       *@@@@         @@@@@     @@@@@@@@@@@.      @@@@@@@@@=@@@@# .@@@@-@@@@@@@@@:    @@@@:\n");
    printf(" =:   .=++++=-::::=--=--=.      .-.      *@@@@       -@@@@@:   *@@@@@@@@@@@@@#   .@@@@@@@@@@@@@@@# .@@@@@@@@@@@@@@@@   @@@@=\n");
    printf(" *.    .==++++=-:-=-====--.     .:.      *@@@@@@@@@@@@@@@#    =@@@@*     *@@@@-  @@@@@      @@@@@# .@@@@@:     %%@@@@:  @@@@=\n");
    printf(" *..    -+=====+=::====--.      .::      *@@@@@@@@@@@@@@@@@+  @@@@@       @@@@@ :@@@@:      .@@@@# .@@@@-       @@@@#  @@@@=\n");
    printf(" +:     .=====-===-::-=-:       .-.      *@@@@         @@@@@+ @@@@%%       @@@@@ =@@@@        @@@@# .@@@@.       @@@@%%  @@@@=\n");
    printf(" .:.     .=++=======:...        .+       *@@@@          @@@@%% @@@@@       @@@@@ -@@@@:      .@@@@* :@@@@.       @@@@%%  @@@@=\n");
    printf("  =.      .-+=======.-.        .-.       *@@@@         @@@@@* =@@@@+     =@@@@=  @@@@@      @@@@@: :@@@@.       @@@@%%  @@@@=\n");
    printf("   =.       ::--:..     .     .:-        *@@@@@@@@@@@@@@@@@@   *@@@@@*:+@@@@@%%   =@@@@@@#*@@@@@@@  .@@@@.       @@@@%%  @@@@=\n");
    printf("    -:                    .  .=.         *@@@@@@@@@@@@@@@@+     .@@@@@@@@@@@:     .@@@@@@@@@@@@-   :@@@@.       @@@@%%  @@@@=\n");
    printf("      =:.                  :-.           .-----------:.             =*#*+.           .+*##*-        ----        ----.  ----\n");
    printf("        =-..            ..=:  .                                                                                             \n");
    printf("           :==::....:-==.       .                                                                                           \n");
    printf("\n===========================================================================================================================\n");
    printf("                                         KUT - Kill Unresponsive Tasks                                                      \n");
    printf("===========================================================================================================================\n\n");
}

void list_user_processes() {
    printf("[+]      Procesos activos del usuario...\n");
    printf("--------------------------------------------------\n");
    system("ps -u $USER -o pid,comm");
    printf("--------------------------------------------------\n\n");
}

int is_process_running(const char *process_name) {
    char command[MAX_CMD];
    snprintf(command, sizeof(command), "pgrep -x %s >/dev/null 2>&1", process_name);
    return system(command) == 0;
}

void kill_process_by_name(const char *process_name, int force) {
    char command[MAX_CMD];

    if (force) {
        snprintf(command, sizeof(command), "killall -9 %s 2>/dev/null", process_name);
    } else {
        snprintf(command, sizeof(command), "killall %s 2>/dev/null", process_name);
    }

    printf("\n[>] Ejecutando: %s\n", command);
}

int main() {
    char process_name[MAX_NAME];
    int force_mode = 0;

    print_banner();
    list_user_processes();

    printf("Ingresa el nombre del proceso a cerrar: ");
    if (fgets(process_name, sizeof(process_name), stdin) != NULL) {
        process_name[strcspn(process_name, "\r\n")] = 0;
    }

    if (strlen(process_name) == 0) {
        printf("\n[-] Error: No ingresaste ningun nombre de proceso.\n");
        return 1;
    }

    printf("\n[*] Comprobando si '%s' esta en ejecucion...\n", process_name);
    
    if (!is_process_running(process_name)) {
        printf("[-] Aviso: El proceso '%s' no esta activo o no existe.\n", process_name);
        return 0;
    }

    printf("[!] Proceso Activo. ¿Forzar cierre agresivo (SIGKILL)? (1 = Si, 0 = No): ");
    scanf("%d", &force_mode);

    kill_process_by_name(process_name, force_mode);

    printf("[+] Operacion completada.\n");

    return 0;
}