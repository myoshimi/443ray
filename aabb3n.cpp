#include<iostream>
#include<cmath>

#include"aabb3n.hpp"

using namespace std;

bool AABB3N::cmpx(AABB3N* a, AABB3N* b){
  bool ret=false;
  if(a->max.x < b->max.x){
    ret = true;
  }
  return ret;
}

AABB3N* AABB3N::clone(){
  AABB3N* v;
  v = new AABB3N();
  v->max.set_vector(max.x, max.y, max.z);
  v->min.set_vector(min.x, min.y, min.z);
  return v;
};

void AABB3N::show(){
  cout << "max: ";
  max.show();
  cout << "min: ";
  min.show();
};

void AABB3N::empty(){
    max.set_vector(-HUGE_VAL, -HUGE_VAL, -HUGE_VAL);
    min.set_vector(HUGE_VAL, HUGE_VAL, HUGE_VAL);
};

Vector3 AABB3N::get_gravity_center(){
  Vector3 v;
  v.x = (max.x + min.x) / 2.0;
  v.y = (max.y + min.y) / 2.0;
  v.z = (max.z + min.z) / 2.0;
  return v;
};

void AABB3N::add(Vector3 p){
  if(p.x < min.x) min.x = p.x;
  if(p.x > max.x) max.x = p.x;
  if(p.y < min.y) min.y = p.y;
  if(p.y > max.y) max.y = p.y;
  if(p.z < min.z) min.z = p.z;
  if(p.z > max.z) max.z = p.z;
};

bool AABB3N::intersect(Vector3 viewpoint, Vector3 view_vector){
  REAL tmp;
  REAL txs, txe;
  REAL tys, tye;
  REAL tzs, tze;
  REAL tin, tout; // incidence outgoing
  REAL judge;
  bool ret=true;

  //max.show();
  //min.show();
  //viewpoint.show();
  //view_vector.show();
  
  txs = (min.x - viewpoint.x) / view_vector.x;
  txe = (max.x - viewpoint.x) / view_vector.x;

  tys = (min.y - viewpoint.y) / view_vector.y;
  tye = (max.y - viewpoint.y) / view_vector.y;

  tzs = (min.z - viewpoint.z) / view_vector.z;
  tze = (max.z - viewpoint.z) / view_vector.z;

  // 数値が大きい方がe, 小さい方がsになるように調整
  if(txs > txe){tmp = txs; txs = txe; txe = tmp;}
  if(tys > tye){tmp = tys; tys = tye; tye = tmp;}
  if(tzs > tze){tmp = tzs; tzs = tze; tze = tmp;}

  // 最遠の入射スラブ
  tin = MAX3(txs, tys, tzs);
  /*
  tin = txs;
  if(tin < tys) tin = tys;
  if(tin < tzs) tin = tzs;
  */

  // 最近の出射スラブ
  tout = MIN3(txe, tye, tze);
  /*
  tout = txe;
  if(tout > tye) tout = tye;
  if(tout > tze) tout = tze;
  */

  judge = tout - tin;

  if(judge < 0.0){
    ret = false;
  }

  return ret;
};
