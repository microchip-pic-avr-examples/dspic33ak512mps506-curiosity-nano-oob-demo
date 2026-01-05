/*************************************************************************
 *  © 2025 Microchip Technology Inc.
 *
 *  Project Name:   dsPIC33AK512MPS506 Curiosity Nano OOB Demo
 *  FileName:       main.c
 * 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *  Description: This header contains UART functions declarations.
 *
 *************************************************************************/
/**************************************************************************
 * MICROCHIP SOFTWARE NOTICE AND DISCLAIMER: You may use this software, and
 * any derivatives created by any person or entity by or on your behalf,
 * exclusively with Microchip's products in accordance with applicable
 * software license terms and conditions, a copy of which is provided for
 * your reference in accompanying documentation. Microchip and its licensors
 * retain all ownership and intellectual property rights in the
 * accompanying software and in all derivatives hereto.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products. You
 * agree that you are solely responsible for testing the software and
 * determining its suitability. Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH
 * MICROCHIP'S PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY,
 * TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT
 * LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT,
 * SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE,
 * HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY
 * OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWABLE BY LAW,
 * MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
 * SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *************************************************************************/


/* dsPIC33AK512MPS506 Curiosity Nano OOB Demo Code */

#include "device_config.h"
#include "uart.h"
#include "osc.h"

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <libpic30.h>


static inline uint8_t btn_pressed(void) {      // active-low
    return (PORTCbits.RC3 == 0);
}

int main(void)
{   
    OSCInit();
    UARTInit();
    
    const char intro[] = "dsPIC33AK512MPS506 Curiosity Nano Demo. Please press on-board button to initiate demo.\n\r";
    const char BP[]  = "\n Button pressed! Enjoy the blink. \n\r";
    const char BNP[] = "\n Button not pressed... please press to observe blink. \n\r";

    _CNPUC3 = 1;   // SW0 pull-up; active-low
    _TRISC3  = 1;   // SW0 input
    _TRISD0  = 0;   // LED0 output
    _LATD0   = 0;   // LED off


    // Print startup banner once
    printf(intro);
    
    uint8_t p_sent = 0;   // pressed message sent
    uint8_t r_sent = 0;   // released message sent

    while (1)
    {
        if (btn_pressed())
        {
            __delay_ms(20);                 
            if (btn_pressed())
            {
                LATDbits.LATD0 ^= 1;        
                __delay_ms(100);

                if (!p_sent) {              
                    printf(BP);
                    p_sent = 1;
                    r_sent = 0;
                }
                continue;
            }
        }

        // not pressed
        _LATD0 = 0;
        if (!r_sent) {                      
            printf(BNP);
            r_sent = 1;
            p_sent = 0;
        }
        __delay_ms(10);
    }
}
