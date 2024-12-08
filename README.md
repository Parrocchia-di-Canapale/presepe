# Presepe
Da qualche anno ormai in parrocchia facciamo un piccolo presepe, e abbiamo deciso di animarlo usando un ESP32.

> [!WARNING]
> Il codice è stato scritto per ESP32, e sfrutta delle funzioni specifiche di questa scheda (la gestione del multi-core sfruttando FreeRTOS). Potrebbe non compilare usando altre schede.

> [!TIP]
> Perché il codice funzioni al meglio, è consigliato collegare i pin degli 8 relay per le luci delle case tutti su pin digitali consecutivi, senza interruzioni.

## Il circuito elettrico
Per quest'anno la soluzione che abbiamo scelto per il circuito è quella di usare semplicemente una breadboard a cui sono collegati tutti i pezzi necessari, quindi non descriveremo la realizzazione in quanto possono essere trovati numerosissimi tutorial online su come fare.
Nel momento in cui faremo un PCB dedicato potremmo decidere di renderlo pubblico.

## Il codice
Il codice è stato pensato per essere interamente parametrico: tra le prime righe possiamo trovare tutti i `#define` usati per controllare ogni aspetto delle animazioni.

|             Define                |      Scopo    |
| --------------------------------- | ------------- |
| `#define dayDuration`             | La durata del giorno (in secondi)|
| `#define transitionDuration`      | La durata della transizione tra il giorno e la notte (o viceversa) (in secondi) |
| `#define houseTransitionDuration` | La durata della transizione per l'accensione/spegnimento delle luci delle case (in secondi) |
| `#define housesTransitionDelay`   | Il periodo di tempo che passa dall'inizio del tramonto/alba all'inizio del cambiamento di stato delle case |
| `#define sunPin`                  | Il pin al qualche è collegato il faretto per il sole |
| `#define firstHousePin`           | Il pin del primo relay delle luci delle case |
| `#define lastHousePin 11`         | Il pin dell'ultimo relay delle luci delle case |

Modificando questi `#define` possiamo quindi modificare il comportamento del presepe, per aggiustarlo sulle nostre esigenze.

Per il resto il funzionamento del codice è estremamente semplice: una volta avviato farà un test accendendo e spegnendo tutte le luci per permettere a chi ha costruito il presepe di verificare il corretto funzionamento di tutto, per poi portare la scena a giorno.

Successivamente entrerà nello stato di funzionamento "normale". Verranno infatti lanciate due task (sfruttando, come detto sopra FreeRTOS), utilizzate per gestire il sole e le case.

Il codice che queste due task eseguiranno sarà praticamente lo stesso: aspettare il momento giusto per poi lanciare la transizione dal giorno alla notte, o viceversa, per il loro campo di competenza.