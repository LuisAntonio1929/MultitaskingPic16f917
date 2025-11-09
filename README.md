# MultitaskingPic16f917
Este proyecto desarolla un programa para un PIC que le permite medir una señal de voltaje variable (V), compara dicha señal con un voltaje de referencia (Vref) también variable, mostrar el valor analogico de V y generar parpadeos temporalizados si se preciona un botón; todo esto al mismo tiempo.

## Circuito

<img src="circuito.png" alt="Descripción" style="display:block; margin:auto;">

## Demostración de funcionamiento

![Animación de velocidad](demostracion.gif)

## Cálculos previos

### Cálculo del CCP2

Cargar CCPR2 para lanzar una conversión analógica cada 100ms.

\[
T = \frac{4}{F_{osc}}
\]

### Cálculo del TMR2



### Cálculo del voltaje



---
## Pseudocódigo

```c

```
