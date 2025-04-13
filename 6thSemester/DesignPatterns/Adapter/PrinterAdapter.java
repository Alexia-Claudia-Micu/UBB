package Adapter;

public class PrinterAdapter implements Outlet{
    private USBmicro usbMicro;

    public PrinterAdapter(USBmicro usbMicroReceived){
        usbMicro = usbMicroReceived;
    }

    @Override
    public void charge(){
        System.out.println("Universal charging through usb micro.");
        this.usbMicro.chargeUSBmicro();
    }
}
