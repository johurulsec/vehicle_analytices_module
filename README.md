# WATCHCAM_6.0
# WATCHCAM_6.0
# WATCHCAM-7.0
# WATCHCAM-7.0
# wc-deploy-src-v7
# wc-deploy-src-v7
# watchcam-beta-v3
# watchcam-beta-v3
# watchcam15
# watchcam15
# wc-RT-Unmusk
# wc-RT-Unmusk


AHHH !! Finally its done !! 

What should I think now what I have thought last December on new home filled with Chaos? Its just superb, unbelieveable, absolute Dream!! 

Its simply a result of passionate work, obsessive thoughts and enormous effors of dedication . Its simply may not possible without the love for your passion!!

The idea sparked on my mind within maybe Dec 10~20, 2018 !! And today is Feb 16, 2AM 2019!! 


Within this small amount of time, I hae been solving enormous amount of technical and business challenges!! And now I am thinking myself successful!!

I don;t have nico!! And only 2K on my 3 accounts combined!!

But Im happy though

1. First attempt-> Unmusking with color with Black mask
2. Unmusking Greyscale with Black mask
3. Dual GAN, one for unmusking and another for smoothing

All of them failed terribly. The resultant face were not getting a match bellow 0.6 threshold. I have been kept busy within, inventing the idea of Unattended Attendance MAcchine!! 

Then, after returning for India tour, the provokes of Steve Jobs ignited my thoughts (MAybe)(

One in a lazy afternoon after 1 day returning from the tour, I was experimenting the GAN again/ This time, the dataset size was 50K approx. 
 I quickly decided to change the colorspace that would be easy for A.I. I kept the face image greyscale, but the mask as "RED". This time the results were better, but not as much as I expected for FR. Then I accadentally realized that the surroundings of the face impacts the Generator profoundly. I quickly cropped the face to closest region and kept the RED mask upon for training with only 3K images. And then its the turn for success!!!

I was also keeping in mind for alternative options, like adding FR error to D_loss but the pytorch seems difficult for me right now.
I have generated preety realistic face of myself and tommy. Then I have SR ed it and put it on WC for mass level recognition>> It was a huge success with a match < 0.6. The 1:N matching was realistic with > 78% accuracy.

Then I have dared to do it in reverse, that means RT Face unmusing. The pipeline was already been clumsy, but who dares to give birth to your brainchild??

I have attempted it on 14 Feb, went so far but the image preprocessing pipeine stucked me on head.I am banned on StackOverflow and tereby couldn't ask questions. Then Ive moved to Opencv for all the preprocessing that was needed for seperate bash script execution. But I was disheartened to learn that OpenCv color to greyscal coluldn't latr add color channel!!
 
Today when I awas in office, I have  successfully automated the boot sequence of the JT Server after months after months of trial. The success ignited me by inspiring for a new light of perseverence!!

During my return to home Uber on Bike, I was thinking that what if I convert the greyscale to BGR back and then apply the RED mask? I rushed to home and immediately sitted on my pc for tuning the thing and YES, it worked


The execution of pytorch inside qt also took a lot of patience, but I was keeping a laser focus to the ray of light on the other side of the tunnel I hae been digging for months!! And when I have switched to python 3 and better QPRocess exec API reference, the code worked like a charm.

So with adequate light, the AI can now successfully Unmusk and recognize HUman face !!! PROVED!! For the first time in the history of mankind, its PROVED!!

A Successful day after multiple succeessful days !!  Rocket can go high, but imaginations go higher!!
# wc-RT-Unmusk
# watchcam-testedOK
# watchcam-testedOK
# WC-DS4-MainWindow-Integrated
