# Taller No 1: Manejo de Memoria Dinámica y Arreglos FIFO en C 

## Objetivo del taller:
Aplicar estructuras dinámicas y manejo de memoria con `malloc` y `free`, a través del desarrollo de un sistema de gestión de elementos usando arreglos tipo FIFO con el manejo de apuntadores para enlaces simples.

---

## Contexto del reto:
Estás diseñando una aplicación para gestionar una lista de productos en una bodega. Cada producto se representa como un nodo. El sistema debe permitir al usuario **registrar, buscar, eliminar, mostrar y contar los productos registrados**.
---

## Reglas para la entrega:
1. **Maximo Dos Personas por Trabajo**
2. **Su código no debe ser igual (o similar en logicas especificas a otro grupo)**
3. **Subir su código al repositorio individual de cada uno**
4. **La fecha limite para publicar en el repositorio es el dia martes 18 de marzo de 2025 a las 08:00 AM**
5. **El código será revisado en la sección de clase. Todos los grupos deben venir.**
6. **El uso de IA solo como referencia el código debe ser sustentado por cada persona al 100%**


---

## Requisitos del sistema:
1. **Agregar Producto**
   - Cada producto tiene: 
     - `ID` (int)
     - `Nombre` (string[30])

2. **Mostrar todos los productos**
   - Muestra `ID` y `Nombre` de cada producto.

3. **Buscar producto por ID**

4. **Eliminar producto por ID**
   - Liberar correctamente la memoria al eliminar.

5. **Contar productos registrados**

6. **Modificar nombre del producto dado un ID**
7. **Liberar memoria al salir del sistema**


## Sugerencia de menú:
1. Agregar producto  
2. Mostrar productos  
3. Buscar producto  
4. Eliminar producto  
5. Contar productos  
6. Modificar productos  
7. Salir  

---

## Evaluación sugerida del taller (con puntuación):
| **Criterio**                        | **Puntaje** |
|-------------------------------------|-------------|
| Agregar producto                    | 15 pts      |
| Mostrar productos                   | 10 pts      |
| Buscar producto                     | 10 pts      |
| Eliminar producto (gestión correcta de memoria) | 35 pts      |
| Contar productos                    | 10 pts      |
| Modificar productos                 | 10 pts      |
| Buen manejo del código y comentarios| 10 pts      |
| **Total**                           | **100 pts** |
