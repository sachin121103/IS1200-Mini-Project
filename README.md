## IS1200-Mini-Project
Mini Project for the IS1200 - Computer Hardware Engineering course at KTH


# Big Picture

Get the audio input, figure out the frequencies using FFT analysis, split them up and visualise the sound using bars. 

# Getting the Sound into the Board

Challenge: The audio input is analog, and it needs to made digital for the FPGA board to understand. Luckily for us, we have an inbuilt ADC (Analog-To-Digital) converter to do this conversion. Challenge is manifold:

1. Storing quick changes in audio samples
2. Match the sampling rate - The FPGA must read in the samples at the same rate the ADC samples it.

# Understanding Frequencies and FFTs

ADC gives us the audio in the time domain and it needs to be converted to frequency domain. This is done with a Fast Fourier Transform (basic implementation). This will tell us the bass, middle and treble. 

Challenge 1: FFTs sample through blocks of samples. The amount of blocks need to be optimised to balance for precision (more samples more precise)
and speed (less samples, quicker). 

Challenge 2: Developing the FFT itself to run on the board. There is something called the Altera FFT IP Core.

Output is Real and Imaginary numbers. To get the strength, we can either take the magnitude (square root of Im^2 + Re^2) or do abs(Re) + abs(Im).

The output will give us hundreds of bins, which is to be classified into one bar-Bass, Low mids, high mids, Trebles and Scale logarithmically. 
Possible enhancement: Color coding each bar. 

# Drawing on Screen with the VGA

VGA needs to generate the following:

1. HSYNC - When does a line start
2. VSYNC - When does a Frame Start
3. RGB signals - What colour each pixel should be.

We also need to implement the pixel painting logic using height and width requirements. 

Bars must be updated at LEAST 60hz to match frame rate.

# Integration and Pipeline

ADC captures sound ---> FFT turns sample into frequency data ---> Bar mapper groups bins into bars ---> VGA controller draws bars on screen.

Use buffers (First In First Out) between each stage and account for latency and clock domains.
