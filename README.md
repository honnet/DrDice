# Dr Dice!

A noisy knitted dice made in Noise bridge, with just a few Dr Who references.

## What ?

This project is the result of a stupid collaboration, during a stupid hackathon in a stupid hackerspace. It's about a knitted dice with some stupid electronics inside, if you throw it, a sound when is played when it stops on a face. Those faces have different pictures related to the famous Dr. Who, and their associated sounds:
* Dalek
* TARDIS
* Sonic Screwdriver
* Random
* Cyberman
* Dr Who

## How?

Technically, here is what we used:
* Accelerometer LSM303DLM (+unused gyro & compass) from http://pololu.com/product/1265
* Mini Audio FX Board from http://adafru.it/23411
* Amplification circuit from http://adafru.it/2130
* Speaker from http://adafru.it/1890
* Charging circuit from http://adafru.it/1905
* later: LEDs ?

## Drivers

* Accelerometer: we used a modified version of the LSM303 driver from pololu, it's in this repo.
* Sound Board: we used the Adafruit driver from github, but it's embedded in this repo
to be sure that it works even if they modify it.

