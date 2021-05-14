#include <senseBoxIO.h>
#include <phyphoxBle.h> 
#include <HDC100X.h>

HDC100X HDC(0x40);

void setup()
{
   HDC.begin(HDC100X_TEMP_HUMI,HDC100X_14BIT,HDC100X_14BIT,DISABLE);
   PhyphoxBLE::start("senseBox MCU");

   //Experiment
   PhyphoxBleExperiment plotHdcValues;   //generate experiment on Arduino which plot random values

   plotHdcValues.setTitle("Temperature Humidity Plotter");
   plotHdcValues.setCategory("senseBox Experiments");
   plotHdcValues.setDescription("Read values from HDC1080 sensor and plot with phyphox afterwards");

   //View
   PhyphoxBleExperiment::View firstView;
   firstView.setLabel("FirstView"); //Create a "view"

   //Graph
   PhyphoxBleExperiment::Graph firstGraph;      //Create graph which will plot random numbers over time     
   firstGraph.setLabel("Temperature over time");
   firstGraph.setUnitX("s");
   firstGraph.setUnitY("C");
   firstGraph.setLabelX("time");
   firstGraph.setLabelY("Temperature");

   /* Assign Channels, so which data is plotted on x or y axis 
   *  first parameter represents x-axis, second y-axis
   *  Channel 0 means a timestamp is created after the BLE package arrives in phyphox
   *  Channel 1 to N corresponding to the N-parameter which is written in server.write()
   */

   firstGraph.setChannel(0,1);

   //Second Graph
   PhyphoxBleExperiment::Graph secondGraph;      //Create graph which will plot random numbers over time     
   secondGraph.setLabel("Humidity over time");
   secondGraph.setUnitX("s");
   secondGraph.setUnitY("%");
   secondGraph.setLabelX("time (s)");
   secondGraph.setLabelY("Humidity");
   //secondGraph.setStyle("dots");

   /* Assign Channels, so which data is plotted on x or y axis 
   *  first parameter represents x-axis, second y-axis
   *  Channel 0 means a timestamp is created after the BLE package arrives in phyphox
   *  Channel 1 to N corresponding to the N-parameter which is written in server.write()
   */

   secondGraph.setChannel(0,2);

   firstView.addElement(firstGraph);            //attach graph to view
   firstView.addElement(secondGraph);            //attach second graph to view
   plotHdcValues.addView(firstView);         //Attach view to experiment
   PhyphoxBLE::addExperiment(plotHdcValues);      //Attach experiment to server

}


void loop()
{
    
  float humi = HDC.getHumi(); 
  float temp = HDC.getTemp();
  
  /*  The random number is written into Channel 1
   *  Up to 5 Channels can written at the same time with server.write(randomDistance, valueChannel2, valueChannel3.. )
   */

  PhyphoxBLE::write(temp, humi);
  delay(50);

  PhyphoxBLE::poll(); //Only required for the Arduino Nano 33 IoT, but it does no harm for other boards.
}
