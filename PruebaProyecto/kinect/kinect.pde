import kinect4WinSDK.Kinect;
import kinect4WinSDK.SkeletonData;
 
Kinect kinect;
ArrayList <SkeletonData> bodies;
float[] manoIzquierda={0,0};
boolean detectarMano = false;
PrintWriter output;
void setup()
{
  size(1000, 1000);
  surface.setTitle("Movimientos con el kinect c:<");
  background(0);
  kinect = new Kinect(this);
  bodies = new ArrayList<SkeletonData>();
  
}
 
void draw()
{
  background(50);
  line(0.7*width,0,0.7*width,height);
  line(0.35*width,0,0.35*width,height);
  line(0,0.7*height,width,0.7*height);
  line(0,0.2*height,width,0.2*height);
  for (int i=0; i<bodies.size (); i++) 
  {
    
    drawSkeleton(bodies.get(i));
    getPosition(bodies.get(i));

  }
}
void getPosition(SkeletonData _s)
{
  //handPosition(_s,Kinect.NUI_SKELETON_POSITION_HAND_LEFT);
  handPosition(_s,Kinect.NUI_SKELETON_POSITION_HAND_RIGHT);

}

 void handPosition(SkeletonData _s, int joint)
 {
   noFill(); 
   char c='r';
  if(detectarMano == false){
    
    manoIzquierda[0] = _s.skeletonPositions[joint].x;
    manoIzquierda[1] = _s.skeletonPositions[joint].y;
    
    stroke(0, 255, 255);
    textSize(30);
    text("X: "+_s.skeletonPositions[joint].x,20,80);
    text("Y: "+_s.skeletonPositions[joint].y,20,120);
    text("X:                              ",20,80);
    text("Y:                              ",20,120);
   
   if(_s.skeletonPositions[joint].x>0.7){
    c='r';
    println("derecha");
   }
   
   if(_s.skeletonPositions[joint].x<0.35){
   c='l';
   println("izquierda");
   }
   
   if(_s.skeletonPositions[joint].y>0.7){
   c='d';
   println("abajo");
   }
   
   if(_s.skeletonPositions[joint].y<0.2){
   c='u';
   println("arriba");
   }
   if(_s.skeletonPositions[joint].x < 0.7 && _s.skeletonPositions[joint].x > 0.35
     && _s.skeletonPositions[joint].y >0.2 && _s.skeletonPositions[joint].y<0.7)
   {
     c='c';
     println("centro");
   }
    detectarMano = true; 
    escribirArchivo(c);

  } else if (_s.skeletonPositionTrackingState[joint] != Kinect.NUI_SKELETON_POSITION_NOT_TRACKED) {
    manoIzquierda[0] = _s.skeletonPositions[joint].x;
    manoIzquierda[1] = _s.skeletonPositions[joint].y;
     
  }
{
  detectarMano=false;
}
 }
void drawSkeleton(SkeletonData _s) 
{
  // Body
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_HEAD, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_CENTER);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_CENTER, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_LEFT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_CENTER, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_RIGHT);
  DrawBone(_s,
  Kinect.NUI_SKELETON_POSITION_SHOULDER_CENTER, 
  Kinect.NUI_SKELETON_POSITION_SPINE);
  
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_SPINE, 
  Kinect.NUI_SKELETON_POSITION_HIP_CENTER);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_HIP_CENTER, 
  Kinect.NUI_SKELETON_POSITION_HIP_LEFT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_HIP_CENTER, 
  Kinect.NUI_SKELETON_POSITION_HIP_RIGHT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_HIP_LEFT, 
  Kinect.NUI_SKELETON_POSITION_HIP_RIGHT);
 
  // Left Arm
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_LEFT, 
  Kinect.NUI_SKELETON_POSITION_ELBOW_LEFT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_ELBOW_LEFT, 
  Kinect.NUI_SKELETON_POSITION_WRIST_LEFT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_WRIST_LEFT, 
  Kinect.NUI_SKELETON_POSITION_HAND_LEFT);
 
  // Right Arm
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_SHOULDER_RIGHT, 
  Kinect.NUI_SKELETON_POSITION_ELBOW_RIGHT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_ELBOW_RIGHT, 
  Kinect.NUI_SKELETON_POSITION_WRIST_RIGHT);
  DrawBone(_s, 
  Kinect.NUI_SKELETON_POSITION_WRIST_RIGHT, 
  Kinect.NUI_SKELETON_POSITION_HAND_RIGHT);
 
  
}
 
void DrawBone(SkeletonData _s, int _j1, int _j2) 
{
  noFill();
  stroke(0, 255, 255);
  if (_s.skeletonPositionTrackingState[_j1] != Kinect.NUI_SKELETON_POSITION_NOT_TRACKED &&
    _s.skeletonPositionTrackingState[_j2] != Kinect.NUI_SKELETON_POSITION_NOT_TRACKED) {
    line(_s.skeletonPositions[_j1].x*width, 
    _s.skeletonPositions[_j1].y*height, 
    _s.skeletonPositions[_j2].x*width, 
    _s.skeletonPositions[_j2].y*height);
  }
}
 void escribirArchivo(char n) { 
  output = createWriter("movimientos.txt");
  output.print(n); // Write the coordinate to the file
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
   // Stops the program
}
void appearEvent(SkeletonData _s) 
{
  if (_s.trackingState == Kinect.NUI_SKELETON_NOT_TRACKED) 
  {
    return;
  }
  synchronized(bodies) {
    bodies.add(_s);
  }
}
 
void disappearEvent(SkeletonData _s) 
{
  synchronized(bodies) {
    for (int i=bodies.size ()-1; i>=0; i--) 
    {
      if (_s.dwTrackingID == bodies.get(i).dwTrackingID) 
      {
        bodies.remove(i);
      }
    }
  }
}
 
void moveEvent(SkeletonData _b, SkeletonData _a) 
{
  if (_a.trackingState == Kinect.NUI_SKELETON_NOT_TRACKED) 
  {
    return;
  }
  synchronized(bodies) {
    for (int i=bodies.size ()-1; i>=0; i--) 
    {
      if (_b.dwTrackingID == bodies.get(i).dwTrackingID) 
      {
        bodies.get(i).copy(_a);
        break;
      }
    }
  }
}
