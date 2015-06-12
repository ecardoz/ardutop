# Ardutop
# Coded by: Edgar C. Cardoz
# email: ecardoz@idun.com.mx
# web: www.idun.com.mx
# Comunicacion con el puerto serial
# Se envian datos a la placa Arduino

from time import sleep
import time
import serial
import psutil

class FreeMemLinux(object):

    """
    Non-cross platform way to get free memory on Linux. Note that this code 
    uses the key word as, which is conditionally Python 2.5 compatible!
    If for some reason you still have Python 2.5 on your system add in the head
    of your code, before all imports:
    from __future__ import with_statement
    """

    def __init__(self, unit='kB'):

        with open('/proc/meminfo', 'r') as mem:
            lines = mem.readlines()

        self._tot = int(lines[0].split()[1])
        self._free = int(lines[1].split()[1])
        self._buff = int(lines[2].split()[1])
        self._cached = int(lines[3].split()[1])
        self._shared = int(lines[20].split()[1])
        #self._swapt = int(lines[14].split()[1])
        #self._swapf = int(lines[15].split()[1])
        #self._swapu = self._swapt - self._swapf

        self.unit = unit
        self._convert = self._faktor()

    def _faktor(self):
        """determine the convertion factor"""
        if self.unit == 'kB':
            return 1
        if self.unit == 'k':
            return 1024.0
        if self.unit == 'MB':
            return 1/1024.0
        if self.unit == 'GB':
            return 1/1024.0/1024.0
        if self.unit == '%':
            return 1.0/self._tot
        else:
            raise Exception("Unit not understood")

    @property
    def total(self):
        return self._convert * self._tot

    @property
    def used(self):
        return self._convert * (self._tot - self._free)

    @property
    def used_real(self):
        """memory used which is not cache or buffers"""
        return self._convert * (self._tot - self._free - self._buff - self._cached)

    @property
    def shared(self):
        return self._convert * (self._tot - self._free)

    @property
    def buffers(self):
        return self._convert * (self._buff)

    @property
    def cached(self):
        return self._convert * self._cached

    @property
    def user_free(self):
        """This is the free memory available for the user"""
        return self._convert *(self._free + self._buff + self._cached)

    @property
    def swap(self):
        return self._convert * self._swapt

    @property
    def swap_free(self):
        return self._convert * self._swapf

    @property
    def swap_used(self):
        return self._convert * self._swapu

def agregar_ceros(numero_sin_ceros):
    strm = ""
    if numero_sin_ceros < 1000:
        if numero_sin_ceros < 100:
            if numero_sin_ceros < 10:
                strm += "000"
            else:
                strm += "00"
        else:
            strm += "0"
    strm += str(numero_sin_ceros)
    return strm

print "Iniciando... "
a = True
current_milli_time = lambda: int(round(time.time() * 1000))
#sleep(5)
try:
    puerto = serial.Serial('/dev/ttyUSB0',9600)
    print "Arduino conectado"
    sleep(3)
except Exception:
    a = False
    print "No hay Arduino conectado en el puerto especificado"

total_ram = 0

while a:
    puerto.flushOutput()
    stream         = ""
    milli          = current_milli_time()
    #f              = FreeMemLinux()
    #used_real_ram  = (int(round(f.used_real))/1024)
    #cache_ram      = int(round(f.cached + f.buffers)/1024)
    #used_ram       = int(round(f.used)/1024)
    #free_ram       = int(round(f.total-f.used))/1024
    #total_ram_aux  = int(used_ram) + int(free_ram)
    perCPU         = psutil.cpu_percent(interval=0.20, percpu=True)    #Array

    ram            = psutil.virtual_memory()
    total_ram      = int(getattr(ram, "total")/1024)/1024
    free_ram       = int(getattr(ram, "free")/1024)/1024
    cache_ram      = int(getattr(ram, "cached")/1024)/1024 + int(getattr(ram, "buffers")/1024)/1024
    used_real_ram  = total_ram - free_ram - cache_ram

    #if total_ram_aux > total_ram:
    #	total_ram = total_ram_aux
    
    for i in range(len(perCPU)):
        if int(round(perCPU[i]))<100:
            if int(round(perCPU[i]))<10:
                stream += "00"
            else:
                stream += "0"
        stream += str(int(round(perCPU[i])))

    #print "used ram: " + str(used_real_ram)
    #print "free ram: " + str(free_ram)
    #print "cache ram: " + str(cache_ram)
    #print "total ram: " + str(total_ram)

    stream += agregar_ceros(used_real_ram)
    stream += agregar_ceros(free_ram)
    stream += agregar_ceros(cache_ram)
    stream += agregar_ceros(total_ram)

    puerto.write(stream)
    print str(current_milli_time() - milli) + "|" + time.ctime(time.time()) + " " + stream + "|" + str(len(stream))
