```mermaid
  
  graph TD
   
      A["`**Perform**
    **R1**: Volume **S1**: Effects
    **R2**: Gain   **S2**: Save Current 
    **R3**: Tone   **S3**: Load / Save 
    **Foot**: Toggle A and B`"]
    
  B["`**Effects**
    **R1**: Choose **S1**: select
    **R2**: SubParam   **S2**: Save&Exit
    **R3**: Value   **S3**: Cancel 
    **Foot**: -`"]

  C["`**Load**
    **R1**: Bank **S1**: Load
    **R2**: Rig   **S2**: Save&Exit 
    **R3**: -   **S3**: Cancel 
    **Foot**: Toggle A and B`"]

  D["`**Save**
    **R1**: Bank **S1**: Select
    **R2**: Rig  **S2**: Save&Exit 
    **R3**: -   **S3**: Cancel 
    **Foot**: Toggle A and B`"]

   B -- Cancel / Save &Exit --> A
   C -- Cancel / Save &Exit --> A
   D -- Cancel / Save &Exit --> A
   A -- S3 Short --> C
   A -- S3 Long --> D
   A -- S1  --> B


```

### Main Classes

```mermaid
classDiagram
direction TD
    class InputActuatorEventType {
        <<enumeration>>
        BUTTON_RISING_EDGE
        BUTTON_FALLING_EDGE
        ROTARY_ENCODER_LEFT
        ROTARY_ENCODER_RIGHT
    }

    class InputEventType {
        <<enumeration>>
        TOGGLE_BUTTON_1_SHORT
        TOGGLE_BUTTON_1_LONG
        ...
        TOGGLE_BUTTON_1_2_LONG
        ...
        ROTARY_ENCODER_1_LEFT_SLOW
        ROTARY_ENCODER_1_RIGHT_SLOW
        ROTARY_ENCODER_1_LEFT_FAST
        ROTARY_ENCODER_1_RIGHT_FAST
        ...
    }

    class IInputActuatorsEvents {
        <<interface>>
        +~setInputActuatorEvent(InputActuatorEventType inputActuatorEvent)
    }

    class IInputEvents {
        <<interface>>
        +~setInputEvent(InputEventType inputEvent)
    }
    
    class IHmiEvents {
        <<interface>>
        +~setToggleSound()
    }

    class IOutputEvents {
        <<interface>>
        +~setOutputEvent(int index, int value)
        +~setOutputEvent(int startIndex, List<int> values)
    }

    class PotiIcIf {
        <<interface>>
        +~set_val_volatile(int poti_id, int value)
    }

    class IOutputActuatorEvents {
        <<interface>>
        +~setOutputActuatorEvent(List <int> indices, List <int> values)
    }

    class InputActuatorsImpl {
        -IInputActuatorsEvents* eventGenerator
        +InputActuatorsImpl(IInputActuatorsEvents* generator)
        +simulateActuatorEvent(InputActuatorEventType inputActuatorEvent)
    }

    class InputEventsImpl {
        -IInputEvents* eventHandler
        +InputEventsImpl(IInputEvents* handler)
        +setInputActuatorEvent(InputActuatorEventType inputActuatorEvent)
    }

    class OutputEventsImpl {
        -IOutputEvents* eventHandler
        +OutputEventsImpl(IOutputEvents* handler)
        +setOutputEvent(int index, int value)
        +setOutputEvent(int startIndex, List<int> values)
    }

    class OutputActuatorImpl {
        <<interface>>
        +setOutputActuatorEvent(List <int> indices, List <int> values)
    }

    class Hmi {
        +setInputEvent(InputEventType inputEvent)
    }

    class Sound {
        +setToggleSound()
    }

    class Mp44xx {
       +set_val_volatile(int poti_id, int value)
    }

    class `SoundSetting`{
    -val: List ~int~
    +getN() int
    +getCurrentValue(int i) int
    +setCurrentValue(int i, SoundSettingParams param) int
    }

    class `SoundSettingParams`{
        -default: List ~int~
        -min: List ~int~
        -max: List ~int~
        +getN() int
        +getMax(int i) int
        +getMin(int i) int
    }

    IInputActuatorsEvents <|.. InputEventsImpl
    IInputEvents <|.. Hmi
    Hmi --> IHmiEvents
    IHmiEvents <|.. Sound
    InputEventType <|.. IInputEvents
    InputActuatorEventType <|.. IInputActuatorsEvents
    InputActuatorsImpl --> IInputActuatorsEvents
    InputEventsImpl --> IInputEvents
    IOutputEvents <|.. OutputEventsImpl
    IOutputActuatorEvents <--  OutputEventsImpl
    IOutputActuatorEvents <|.. OutputActuatorImpl
    Sound --> IOutputEvents
    SoundSettingParams  <--  SoundSetting 
    Sound --> SoundSetting
    PotiIcIf <--  OutputActuatorImpl
    PotiIcIf <|.. Mp44xx

```


### Button Sequence Example

```mermaid
sequenceDiagram
    InputActuators ->> InputActuators: Sw1 off -> on
    InputActuators ->> Inputevents:  ActuatorEvent (1, true)
    InputActuators ->> InputActuators: Sw1 on -> off
    InputActuators ->> Inputevents:  ActuatorEvent (1, off)
    Inputevents ->> Hmi: VirtualActuatorEvent (1,Short)
    Hmi ->>Sound: toggleSound()
    Sound ->> Sound: activeSound =1-activeSound
    Sound ->> OutputActuators: For all in i: <br>If value changed: <br> setVolatileValue (i,SoundSetting.val[i])
    OutputActuators ->> OutputActuator: setVolatileValue(val)
    OutputActuator ->> PotiIC: I2CWrite Value
```
