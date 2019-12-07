pi = 3.141592;
sin(pi/2)					# 1
log(1)						# 0
exp(0)						# 1
log(exp(pi))					# 3.141592	
sqrt(4)						# 2
pow(2,2)				# 4
hypot(4,3)				# 5
lerp(0,10,0.3)				# 3
polynome(3,1,0,3,2,2)			# 29
(3  + log(1)/2)/hypot(2,3)		# 0.83205029
nested = lerp(2,pow(2,3),hypot(.2,.3));	# 2 + 0.360555 * ( 8 - 2 )  = 4.16333
polynome( log(exp(4)), lerp(1,2 ,  0.3),  sin(cos(6)), hypot(pow(3,2),  sqrt(exp(3)) ), tan(3/4),exp( cos( lerp(5,-2,0.3) ) ), 2.979890987654456798 ) # 147.532
