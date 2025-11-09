# MultitaskingPic16f917
Este proyecto desarolla un programa para un PIC que le permite medir una señal de voltaje variable (V), compara dicha señal con un voltaje de referencia (Vref) también variable, mostrar el valor analogico de V y generar parpadeos temporalizados si se preciona un botón; todo esto al mismo tiempo.

## Circuito

<img src="circuito.png" alt="Descripción" style="display:block; margin:auto;">

## Demostración de funcionamiento

![Animación de velocidad](demostracion.gif)

## Especificaciones de Hardware

- Frecuencia de oscilacion: 8MHz
- 10 bits para la conversion ADC
- Reloj de oscilacion interno

## Modulos empleados

- Timer 1
- Timer 2
- CCP2
- Comparador Analógico

## Cálculos previos

### Cálculo del CCP2

Cargar CCPR2 para lanzar una conversión analógica cada 100ms.

$$
T = \frac{4\cdot PRESCALER\cdot CCPR2}{F_{osc}}
$$

Dado que se emplea un prescaler de 1:16, un reloj interno de 8MHz, se llega a que el valor de CCPR2 es 50000.

### Cálculo del TMR2

TMR2 debe llegar a hacer match con PR2 en un tiempo de 27.776ms repitiendose esto 18 veces para llegar a 499.968ms (muy cercano a los 500ms de duracion del encendido y apagado durante el parpadeo).

$$
T = \frac{4\cdot PRESCALER \cdot POSTCALER \cdot (PR2+1)}{F_{osc}}
$$

Trabajando con un prescaler y postcaler de 1:16 ambos, se llega a que el valor de PR2 es de 216.

### Cálculo del voltaje

Sabiendo que el valor de 0v corresponde al valor digital de 0, y que 5v corresponde a 1023, se procede a aplicar la siguiente formula para obtener un voltaje en unidades de centivoltios:

$$
V = ADRES\frac{500}{1023}
$$

Sin embjargo, en C esto consume mucha memoria, por lo que aplicando desplazamiento en bits se llega a:

$$
V = (ADRES>>1)-(ADRES>>6)+(ADRES>>8)
$$

---
## Pseudocódigo

```c

```
