#include <iostream>
#include <string>
#include <algorithm>
#include <sys/time.h>

using namespace std;

// Función para buscar coincidencias en una ventana de tamaño m
 void directo(const string& A, const string& B, int ini, int fin, int m, int& p, int& max_coincidencias) {
    // Solo procesar hasta donde sea posible formar subcadenas de tamaño m
    const int limit = fin - m + 1;
    
    
    for (int pos = ini; pos <= limit; ++pos) {
        int coincidencias = 0;
        
        // Contar coincidencias
        for (int j = 0; j < m; ++j) {
            if (A[pos + j] == B[pos + j]) {
                coincidencias++;
            }
        }
        
        // Actualizar máximo si es necesario
        if (coincidencias > max_coincidencias) {
            max_coincidencias = coincidencias;
            p = pos + 1; // Mantener posición 1-indexada
        }
    }
}

// Función recursiva
void dyv(const string& A, const string& B, int ini, int fin, int m, int& p, int& max_coincidencias) {
   
    
    // Umbral para cambiar a procesamiento directo
    const int cambiar_directo = 2*m; // Aumentado para reducir la recursión
    
    if (fin - ini + 1 <= cambiar_directo||A.length()==m||B.length()==m) {
        // Caso base: procesar directamente
        directo(A, B, ini, fin, m, p, max_coincidencias);
        return;
    }
    
    int mid = (ini + fin) / 2;
    
    // Recursión sobre la parte izquierda
    dyv(A, B, ini, mid, m, p, max_coincidencias);
    
    
    
    // Recursión sobre la parte derecha
    dyv(A, B, mid + 1, fin, m, p, max_coincidencias);
    
    
    
    // Procesar SOLO las subcadenas que cruzan el punto medio
    int inicio_cruce = max(ini, mid - m + 1);
    int fin_cruce = min(mid, fin - m + 1);
    
    // Solo procesar la región de cruce si hay subcadenas válidas
    if (inicio_cruce <= fin_cruce) {
        for (int pos = inicio_cruce; pos <= fin_cruce; ++pos) {
            
            
            int coincidencias = 0;
            
            // Contar coincidencias
            for (int j = 0; j < m; ++j) {
                if (A[pos + j] == B[pos + j]) {
                    coincidencias++;
                }
            }
            
            // Actualizar máximo si es necesario
            if (coincidencias > max_coincidencias) {
                max_coincidencias = coincidencias;
                p = pos + 1; // Mantener posición 1-indexada
            }
        }
    }
}

int main() {
   
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL); // Instante inicial
    printf("Lee este mensaje y pulsa ENTER\n");
    getchar();
    
    string A, B;
    
    int m;
    
    cin >> A >> B >> m;
    
    int p = 0;
    int max_coincidencias = -1;
    
    
    dyv(A, B, 0, A.length() - 1, m, p, max_coincidencias);
    cout << p << " " << max_coincidencias << endl;
    
    gettimeofday(&tf, NULL); // Instante final 
    tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec -
    ti.tv_usec)/1000.0;
    printf("Has tardado: %g milisegundos\n", tiempo);
    
    return 0;
}