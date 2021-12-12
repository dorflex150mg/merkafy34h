class FireStrategyTriple {
   
   FireProjectile fire_projectile(int posx, int posy, int movement_counter, int fire_interval, int type, int *position_counter) {
      if(movement_counter % fire_interval == 0 || position_counter > 0) {
         /* choosing cannon - half of the times, the movement counter 
          * is divisible by half of the fire intervals (2n/2 vs (2n + 1)/2)*/
         if(movement_counter % (fire_interval/2) == 0) {
            position_counter = 3;
            proj_posx = posx + CANNION1RELATIVEX;
         } else {
            position_counter = 3;
            proj_posx = posx + CANNION2RELATIVEX;
         }
         proj_posy = posy + BOSS1HEIGHT;
         position_counter -= 1;
         return new EnemyProjectile(proj_posx, proj_posy, TYPEM1, position_counter); 
      }
      return nullptr;
   }
}; 
