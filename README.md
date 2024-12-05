# Presepe
Da qualche anno ormai in parrocchia facciamo un piccolo presepe, e abbiamo deciso di animarlo usando un Arduino Uno R4.

> [!WARNING]
> Il codice è stato scritto per Arduino UNO R4 (Minima o Wi-Fi, è indifferente), e sfrutta delle funzioni specifiche di questa scheda (la matrice LED). Non compilerà usando altre schede.

> [!TIP]
> Perché il codice funzioni al meglio, è consigliato collegare i pin degli 8 relay per le luci tutti su pin digitali consecutivi, senza interruzioni.

## Il circuito elettrico
TODO

## Il codice
Il codice è stato pensato per essere interamente parametrico: tra le prime righe possiamo trovare tutti i `#define` usati per controllare ogni aspetto delle animazioni.

|             Define                |      Scopo    |
| --------------------------------- | ------------- |
| `#define dayDuration`             | La durata del giorno (in secondi)|
| `#define transitionDuration`      | La durata della transizione tra il giorno e la notte (o viceversa) (in secondi) |
| `#define houseTransitionDuration` | La durata della transizione per l'accensione/spegnimento delle luci delle case (in secondi) |
| `#define sunPin`                  | Il pin al qualche è collegato il faretto per il sole |
| `#define firstHousePin`           | Il pin del primo relay delle luci delle case |
| `#define lastHousePin 11`         | Il pin dell'ultimo relay delle luci delle case |

Modificando questi `#define` possiamo quindi modificare il comportamento del presepe, per aggiustarlo sulle nostre esigenze.

Per il resto il funzionamento del codice è estremamente semplice: una volta avviato farà un test accendendo e spegnendo tutte le luci per permettere a chi ha costruito il presepe di verificare il corretto funzionamento di tutto, per poi portare la scena a giorno.

Successivamente entrerà nello stato di funzionamento "normale": aspetterà il tempo che abbiamo impostato, per poi fare la transizione dal giorno alla notte (o viceversa) e ricominciare da capo.