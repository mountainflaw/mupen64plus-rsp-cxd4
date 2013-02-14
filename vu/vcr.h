#include "vu.h"

void VCR(int vd, int vs, int vt, int element)
{
    int ge, le;
    register int i, j;

    VCC = 0x0000;
    if (element == 0x0) /* if (element >> 1 == 00) */
        for (i = 0; i < 8; i++)
            if ((VR[vs].s[i] ^ VR[vt].s[i]) < 0)
            {
                ge = (VR[vt].s[i] < 0);
                le = (VR[vs].s[i] + VR[vt].s[i] + 1 <= 0);
                VACC[i].s[LO] = le ? ~VR[vt].s[i] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
            else
            {
                le = (VR[vt].s[i] < 0);
                ge = (VR[vs].s[i] - VR[vt].s[i] >= 0);
                VACC[i].s[LO] = le ? VR[vt].s[i] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
    else if ((element & 0xE) == 02) /* scalar quarter */
        for (i = 0; i < 8; i++)
        {
            j = (i & 0xE) | (element & 01);
            if ((VR[vs].s[i] ^ VR[vt].s[j]) < 0)
            {
                ge = (VR[vt].s[j] < 0);
                le = (VR[vs].s[i] + VR[vt].s[j] + 1 <= 0);
                VACC[i].s[LO] = le ? ~VR[vt].s[i] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
            else
            {
                le = (VR[vt].s[j] < 0);
                ge = (VR[vs].s[i] - VR[vt].s[j] >= 0);
                VACC[i].s[LO] = le ? VR[vt].s[j] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
        }
    else if ((element & 0xC) == 04) /* scalar half */
        for (i = 0; i < 8; i++)
        {
            j = (i & 0xC) | (element & 03);
            if ((VR[vs].s[i] ^ VR[vt].s[j]) < 0)
            {
                ge = (VR[vt].s[j] < 0);
                le = (VR[vs].s[i] + VR[vt].s[j] + 1 <= 0);
                VACC[i].s[LO] = le ? ~VR[vt].s[i] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
            else
            {
                le = (VR[vt].s[j] < 0);
                ge = (VR[vs].s[i] - VR[vt].s[j] >= 0);
                VACC[i].s[LO] = le ? VR[vt].s[j] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
        }
    else /* if ((element & 0b1000) == 0b1000) /* scalar whole */
        for (i = 0, j = element & 07; i < 8; i++)
            if ((VR[vs].s[i] ^ VR[vt].s[j]) < 0)
            {
                ge = (VR[vt].s[j] < 0);
                le = (VR[vs].s[i] + VR[vt].s[j] + 1 <= 0);
                VACC[i].s[LO] = le ? ~VR[vt].s[i] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
            else
            {
                le = (VR[vt].s[j] < 0);
                ge = (VR[vs].s[i] - VR[vt].s[j] >= 0);
                VACC[i].s[LO] = le ? VR[vt].s[j] : VR[vs].s[i];
                VCC |= (ge << (i + 8)) | (le << (i + 0));
            }
    for (i = 0; i < 8; i++)
        VR[vd].s[i] = VACC[i].s[LO];
    VCO = 0x0000;
    VCE = 0x00;
    return;
}
