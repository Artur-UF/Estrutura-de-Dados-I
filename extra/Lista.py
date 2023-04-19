import time

class ListaNodo:

	def __init__(self, info):
		self.info = info
		self.prox = None

	def __str__(self):
		return str(self.info)

class Lista:

	def __init__(self):
		self.prim = None

	def insereInicio(self, info):
		novo = ListaNodo(info)
		novo.prox = self.prim
		self.prim = novo

	def insereFim(self, info):
		ant = None
		nodo = self.prim 
		while(nodo != None):
			ant = nodo
			nodo = nodo.prox
		if (ant == None):
			self.insereInicio(info)
		else:
			novo = ListaNodo(info)
			ant.prox = novo

	def imprime(self):
		print('[')
		nodo = self.prim 
		while(nodo != None):
			print(nodo)
			nodo = nodo.prox
		print(']')

if __name__ == '__main__':
	
	N = 10000

	lista = []
	start_time = time.time()
	for x in range(N):
		lista.insert(0, x)
	print("--- %s seconds ---" % (time.time() - start_time))
	#print(lista)

	lista = []
	start_time = time.time()
	for x in range(N):
		lista.insert(x, x)
	print("--- %s seconds ---" % (time.time() - start_time))
	#print(lista)

	lista = Lista()
	start_time = time.time()
	for x in range(N):
		lista.insereInicio(x)
	print("--- %s seconds ---" % (time.time() - start_time))
	#lista.imprime()

	lista = Lista()
	start_time = time.time()
	for x in range(N):
		lista.insereFim(x)
	print("--- %s seconds ---" % (time.time() - start_time))
	#lista.imprime()

