# Dr Dice!

A noisy knitted dice made in Noise bridge, with just a few Dr Who references.

## What ?

This project is the result of a stupid collaboration, during a stupid hackathon in a stupid hackerspace:
![noisebridge](https://lh3.googleusercontent.com/vej3VOd5sqU_rs2b4-2WLnrc0M20-QCGEmbL3U1Mthe8nmwTkzBNG0v5BymfXs-6lrY3KAx5hHclaykiwz0nhDRyRQRmKzsnyIDMnzyYwTMfOCHHL_z5ywYZfNa0hCkB7BF6FYZhJ7ccjtgD3-bL0cIxnlFV3i8Al28RtJNJ9-1EDw_jf4Wpn3SJ-HaC2LE4sLWn2CIFZjaHeauaOhooc38o7Lz5DZjNUiOZjG8SI976u-WYKp3OW_3dLRYcnJ3JGzs9rWCrRWoV5eE6nx_vghDhFVnGEiKpb5oGlAs-aPHzb70Fb9-ksVnL8zNcGfUnJy5kNnMEO-JLWV4TwRRztipGdbAMdoo2cq2B6p2oiZN6GJi-vDDBtbS6SK221mhVa9HSfOkDLuxaSY4DLrYb8kwOvmEn0z3uWK6oM6-3wxWChhLNeD9WPl74PRymztNUmFXcMVMcLTQz6OJg5ZJ9es9OQFc1GxkIGuIbqPCx7SZ8oyB35FqxfwMOou_qoEUCcA25o8sFnk94nHIueq_onThtijnbcsQCZRzIdixDclAiQ-H_fuX47gUGYbFid0wiVCt_Ti_C_mjt1bB5NIqvSKuLqgOPDkd0S79xyAz02apl36qF7ipvajpXWH2upqtHYBR7xcJZOeNvJe4Q6661YTmEwRYb-hIueFHM0S1H_Ww=w1920-h378-no)

It's about a knitted dice with some stupid electronics inside, if you throw it, a sound when is played when it stops on a face. Those faces have different pictures related to the famous Dr. Who, and their associated sounds:
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

