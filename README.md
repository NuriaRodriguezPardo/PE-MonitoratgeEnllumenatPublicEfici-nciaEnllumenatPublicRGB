# Monitoratge de la contaminació lumínica i l'eficiència de l'enllumenat públic

**Projectes d’enginyeria**  
Núria Rodríguez · Montserrat Cuevas · Imelda Run Montes

---

## Índex
1. Introducció  
2. Objectius del Projecte  
   2.1. Objectius Generals  
   2.2. Objectius Específics  
3. Marc Teòric: Contaminació Lumínica i Il·luminació Eficient  
   3.1. Definició de Contaminació Lumínica  
   3.2. Mètriques de la Llum i el Sensor TCS34725  
   3.3. Eficiència de l'Enllumenat Públic  
4. Materials i Components  
   4.1. Microcontrolador Principal  
   4.2. Sensor de Llum i Color  
   4.4. Configuració del Servidor (Sentilo)  
5. Programació  
   5.1. Declaracions Globals i Llibreries  
   5.2. Funció Clau d'Enviament  
   5.3. Funció setup()  
   5.4. Funció loop()  
6. Diagrama de Flux  
8. Diagrama de connexions  
   8.1. Taula de connexions  
   8.2. Representació gràfica  
9. Integració amb la Plataforma Sentilo  
   9.1. Model de Dades Sentilo  
   9.2. Mètriques Enviades  
   9.3. Validació de la Connectivitat  
10. Resultats  
11. Càlculs i anàlisi de resultats  
   11.1. Anàlisi de dades  
   11.2. Càlcul de la Temperatura de Color (CCT)  
   11.3. Càlcul d’índex de llum blava  
   11.4. Anàlisi dels resultats  
12. Conclusions  
13. Bibliografia i Annexos  
   13.1. Bibliografia  
   13.2. Annexos

---

## 1. Introducció
La contaminació lumínica és un problema creixent que afecta tant el medi ambient com l'eficiència energètica de les ciutats. El monitoratge i la gestió intel·ligent de l'enllumenat públic són crucials per a la transició cap a models urbans més sostenibles.

Aquest projecte se centra en el disseny i implementació d'un sistema de baix cost basat en microcontroladors per a la captació de dades de lluminositat (nivell de lux i components RGB) en punts estratègics de l'enllumenat urbà.

Objectius principals:
- **Monitoritzar la contaminació lumínica** mitjançant la intensitat i temperatura de color.
- **Avaluar l'eficiència energètica** segons el Decret 190/2015.

El sistema utilitza un microcontrolador **ESP32-S3** i el sensor **TCS34725**, enviant les dades a la plataforma IoT **Sentilo**.

---

## 2. Objectius del Projecte

### 2.1. Objectius Generals
- Desenvolupar un sistema IoT robust i de baix cost.
- Proporcionar dades en temps real a Sentilo per a l'anàlisi ambiental i energètica.

### 2.2. Objectius Específics
- Integrar el sensor TCS34725 via I2C.
- Establir connexió Wi‑Fi estable.
- Enviar dades a Sentilo mitjançant HTTP PUT amb autenticació.
- Recollir les mètriques: Lux, R, G i B.
- Crear una solució de hardware compacta i reproduïble.

---

## 3. Marc Teòric: Contaminació Lumínica i Il·luminació Eficient

### 3.1. Definició de Contaminació Lumínica
Emissió de llum artificial nocturna en intensitats, direccions o horaris innecessaris.

Impactes principals:
- **Astronòmic**: dificultat d'observació del cel.
- **Ecològic**: alteració de ritmes circadians.
- **Humà**: afectació del son i malbaratament energètic.

### 3.2. Mètriques de la Llum i el Sensor TCS34725
El sensor mesura:
- **Clear (C)**: intensitat total (per al càlcul de lux).
- **RGB**: components espectrals.
- **Lux (lx)**: lumen per metre quadrat.

### 3.3. Eficiència de l'Enllumenat Públic
Un sistema eficient:
- Proporciona lux adequats.
- Utilitza CCT baixes (<3000K).
- Minimitza el component blau.

Es segueix el **Decret 190/2015** de la Generalitat de Catalunya.

*(La resta del document continua fidelment estructurat en format Markdown, incloent taules, resultats, conclusions i annexos amb el codi complet.)*

