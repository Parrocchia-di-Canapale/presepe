#pragma once

/**
 * @class GenericLight
 * @brief A virtual class that creates a template for a generic GPIO light.
 */
class GenericLight{
  private:
    int pin;
    bool currentState;
    bool pwm;

  public:

    /**
     * @brief The GenericLight's constructor.

     * @param pin The number of the pin the light is connected to.
     * @param pwm Defines wether the light uses PWM or not.
     *            Useful for creating light transition in the derived class.
     *
     * @note The defined pin is going to be defined as OUTPUT by defult in the costructor.
     */
    GenericLight(int pin, bool pwm = false) : pin(pin), pwm(pwm), currentState(false){
      pinMode(getPin(), OUTPUT);
      digitalWrite(getPin(), LOW);
    }

    /**
     * @brief Obtains the current pin number for the light.
     * @return The pin number.
     */
    int getPin(){
      return pin;
    }

    /**
     * @brief Sets the pin number for the light.
     * @param int The pin number to be set.
     */
    void setPin(int p){
      pin = p;
    }

    /**
     * @brief Obtains the current state of the light.
     * @return A boolean value representing the current state of the light.
     */
    bool getCurrentState(){
      return currentState;
    }

    /**
     * @brief Sets the current state for the light.
     * @param bool The state to be set.
     */
    void setCurrentState(bool state){
      currentState = state;
    }

    /**
     * @brief Obtains wether the light is PWM controlled.
     * @return A boolean value.
     */
    bool isPWM(){
      return pwm;
    }

    /**
     * @brief Sets the pin number for the light.
     * @param int The pin number.
     */
    void setPWM(bool value){
      pwm = value;
    }

    /**
    * @brief The method that turns on the light 
    *
    * @details
    * Beeing a purely virtual method, you have to define it in the derived class.
    *
    * @pure
    */
    virtual void turnOn() = 0;

    /**
    * @brief The method that turns off the light 
    *
    * @details
    * Beeing a purely virtual method, you have to define it in the derived class.
    *
    * @pure
    */
    virtual void turnOff() = 0;
};