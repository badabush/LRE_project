/*
 * advancedMoves.c
 *
 *  Created on: 09.02.2020
 *      Author: Willi
 *      Purpose: advanced Moveset for e.g. following Wall, parking, following Corner
 */
#include <advancedMoves.h>

void advancedMoves(void)
{
desiredDist =dummy; // dummy:(command: move ... distance/ ... cells)

	void cmd_forward_wall(void)
	{
		if (dist_L <= xLmin) // follow left wall
		{
			xLold=dist_L;
			for (movedDist=0; movedDist<desiredDist; movedDist++)
			{
				cmd_forward(cellDist); //  mv 1 cell fw; fct has to be changed so you can set a forward driving dist

				xLlive=dist_L;	// measure and save dist to Lwall
				xLdiff=xLlive-xLold;
				reqTurn=tan((2*3.14159265/360)*(abs(xLdiff)/cellDist)); // tan output is in rad
				if (xLdiff<0)
				{
					cmd_Lturn(reqTurn);
				}
				else if (xLdiff>0)
				{
					cmd_Rturn(reqTurn);
				}
				xLold=xLlive;
			}


		}
		else if (dist_R <= xRmin) // follow right wall
		{

		}
	}
}
