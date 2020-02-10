Contribution Guidelines
=======================

Contributions to HML_FwLib_8051 are welcome. If you find a bug or want to improve HML_FwLib_8051 in another way, pull requests are appreciated.

For bigger changes, in order to avoid wasted effort, please open an issue to discuss the technical details before creating a pull request.

The further sections explain the process in more detail and provides some guidelines on how contributions should look like.


Coding Style
------------

* use 4 spaces for indentation
* always use parenthesis for control structures
* use spaces around operators
* lines should not have trailing whitespace
* use pronouncable variable names, not just a combination of letters
* use unified code comment style, you can refer to existing code
* ...

Example:

```c
/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2019/09/22
 * \brief       calculate initial value of counter/timer by specified time length
 * \param[in]   t: expected time length (unit: us)
 * \return      none
 * \ingroup     TIM2
 * \remarks     result is usually written into TH2/TL2
******************************************************************************/
uint16_t TIM2_calculateInitValue(uint16_t t)
{
    if((t*(MCU_FRE_CLK/1000000)/12) >= TIM2_MAXTICK)
    {
        return 0;
    }
    else
    {
        return (TIM2_MAXTICK + 1 - (t*(MCU_FRE_CLK/1000000)/12));
    }
}
```
