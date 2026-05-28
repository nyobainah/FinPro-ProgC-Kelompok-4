#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double rH;
    double kH;
    double rT;
    double kT;
    double beta;
    double alpha;
    double gamma;
    double delta; 
} Parameters; 

void setScenario(Parameters *p, int choice){
    p->rH = 0.03;
    p->kH = 1000.0;
    p->kT = 800.0;
    p->beta = 0.00005;
    p->delta = 0.02;

    if (choice == 1){
        p->rT = 0.08;
        p->alpha = 0.00005;
    } else if (choice == 2){
        p->rT = 0.08;
        p->alpha = 0.0002;
    } else if (choice == 3){
        p->rT = 0.15;
        p->alpha = 0.0001;
    }
}

void inputCustomParameters(Parameters *p){
    printf("\n=== Custom Parameters ===\n");

    printf("Healthy cell growth rate (rH): "); 
    scanf("%lf", &p->rH);

    printf("Healthy cell carrying capacity (kH): ");
    scanf("%lf", &p->kH);

    printf("Tumor growth rate (rT): ");
    scanf("%lf", &p->rT);

    printf("Tumor carrying capacity (kT): ");
    scanf("%lf", &p->kT);

    printf("Healthy-to-tumor interaction rate (beta): ");
    scanf("%lf", &p->beta);

    printf("Immune killing effectiveness (alpha): ");
    scanf("%lf", &p->alpha);

    printf("Immune stimulation rate (gamma): ");
    scanf("%lf", &p->gamma);

    printf("Immune natural death rate (delta): ");
    scanf("%lf", &p->delta);
}

void runSimulation(double H, double T, double I, double dt, double tMax, Parameters p){
    FILE *file = fopen("./hasil_simulasi.csv", "w");
    if (file == NULL){
        printf("Error: failed to create CSV file.\n");
        return;
    }

    fprintf(file, "Time,HealthyCells,TumorCells,ImmuneCells\n");
    int steps = (int)(tMax/dt);

    for (int i =0; i<= steps; i++){
        double time = i*dt;

        fprintf(file, "%.2f, %.4f, %.4f, %.4f\n", time, H, T, I);

        double dHdt = p.rH*H*(1-H/p.kH)-p.beta*H*T;
        double dTdt = p.rT*T*(1-T/p.kT)+p.beta*H*T-p.alpha*I*T;
        double dIdt = p.gamma*I*T-p.delta*I;

        H = H+dt*dHdt;
        T = T+dt*dTdt;
        I = I+dt*dIdt;

        if (H<0) H=0;
        if (T<0) T=0;
        if (I<0) I=0; 
    }

    fclose(file);
    printf("\n=== Simulation Completed ===\n");
    printf("Final Healthy Cells : %.4f\n", H);
    printf("Final Tumor Cells   : %.4f\n", T);
    printf("Final Immune Cells  : %.4f\n", I);
    printf("Result saved to hasil_simulasi.csv\n");
}

int main() {
    Parameters p;

    double H, T, I;
    double dt, tMax;
    int choice;

    do {
    printf("=============================================\n");
    printf(" Tumor-Immune Dynamics Simulation in C\n");
    printf(" SIR-Lotka Volterra Model using Euler Method\n");
    printf("=============================================\n");

    printf("\nChoose simulation scenario:\n");
    printf("1. Weak immune response\n");
    printf("2. Strong immune response\n");
    printf("3. Aggressive tumor growth\n");
    printf("4. Custom parameters\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
        case 2:
        case 3:
            setScenario(&p, choice);
            printf("\n=== Initial Condition ===\n");
            printf("Initial healthy cells :");
            scanf("%lf", &H);
            printf("Initial tumor cells :");
            scanf("%lf", &T);
            printf("Initial immune cells :");
            scanf("%lf", &I);

            printf("\n=== Simulation Settings ===\n");
            printf("Timestep dt :");
            scanf("%lf", &dt);
            printf("Total simulation time :");
            scanf("%lf", &tMax);

            runSimulation(H, T, I, dt, tMax, p);
            break; 

            case 4: 
            inputCustomParameters(&p);
            printf("\n=== Initial Condition ===\n");
            printf("Initial healthy cells :");
            scanf("%lf", &H);
            printf("Initial tumor cells :");
            scanf("%lf", &T);
            printf("Initial immune cells :");
            scanf("%lf", &I);

            printf("\n=== Simulation Settings ===\n");
            printf("Timestep dt :");
            scanf("%lf", &dt);
            printf("Total simulation time :");
            scanf("%lf", &tMax);

            runSimulation(H, T, I, dt, tMax, p);
            break;
        
        case 5:
            printf("\nExiting program...\n");
            printf("Thank you.\n");
            break; 
        
        default: 
            printf("\nInvalid choice.\n");
            printf("Please choose between 1-5.\n"); 
        } 
    } while(choice !=5);
    return 0; 
}

