# Monsoon 2021 - OS Assignment 5

> Pramod Rao B
> 2020111012

## Multi-threaded course portal simulation

Entities being simulated by threads:

- Courses
- Labs
- Students

### General working:

A course consists of a set of valid labs from which it can pick TAs. Each lab has a certain limit on the number of times a student under that lab can become a TA. If a course fails to find a TA to take a tutorial, then it is withdrawn from the course portal. A student who is interested in a course, applies for it and waits until the course approves his selection. He then sits for the tutorial and based on his calibre and the interest quotient of the course he either picks the course permanently in which case he exits the simulation or he goes for his next preference.

- **Course thread**
  1. Iterates over all labs until it finds a lab which has TAs who haven't hit their limit on the number of tutorials taken
  2. If no student has applied for the course, then the course thread waits on the condition variable `emptyCond`.
  3. Once woken up, it iterates through the TA list till it finds a TA who has not hit his limit.
  4. Once found, it locks the TA and allocates it for itself to take a tutorial
  5. The following is how a tutorial takes place:
     1. The TA picks a random positive integer between 1 and `course_max_slot ` call it say, `x`
     2. We calculate `numAttendingTut` as the minimum out of `x` and the number of students who have this course set at their current preference. This indicates the number of students who will actually attend his tutorial
     3. To indicate that that `x` number of eats are now available, he signals a condition variable `openCond` for `numAttendingtut` number of times so that it wakes up exactly that number of students.
     4. The TA then waits for all the students to join the tutorial by sleeping on the condition variable `fullCond` which is signalled by a student whenever he joins the tutorial.
     5. When the expected number of students have joined, the TA finally take the tutorial (implemented as a sleep of 2 seconds)
     6. He then signals `numAttendingTut` number of times again to wake up the student who were in the tutorial
     7. This concludes the tutorial process
  6. Once done with the tutorial, the course increments the counter of the TA and unlocks him
  7. Repeat from step 1 until we find no more valid labs in which case, the course is withdrawn from the portal by setting `course->withdrawn = 1` and the thread exits. In this case, it also broadcasts to account for the students who might be waiting on the condition variable `openCond`
- **Student thread**
  1. The student thread sleeps until it is time for the student's registration
  2. If the current preferred course is already withdrawn, then move onto the next preference or exit thread if this is already the last preference
  3. The student increments the `prefer` counter indicating that he has the course as his current preference
  4. Along with this, he also signals the `emptyCond` condition variable which the course may or may not be sleeping on depending on whether this is the first student who wants the course or not
  5. The student then waits on the condition variable `openCond` for this application to be accepted and get a seat allotted
  6. After waking up, the student checks again if the course is withdrawn since the waking up could have been because of the course being withdrawn broadcast. If it is indeed withdrawn, then he moves onto his next preference/exits
  7. If not, then he joins the tutorial and increments `tutSlots` indicating that he has indeed joined the tutorial and signals `fullCond` which the TA checks to see if the expected number of students have joined for the tutorial
  8. After finishing the tutorial and waking up, the student decides whether to take the course permanently or not based on his calibre and the interest quotient of the course.
  9. If he ends up taking the course, then the thread exits the simulation.
  10. If not, then he either moves down to his next preference or if its already his last preference, then the thread exits the simulation
- **Lab thread**
  1. The labs are more of a resource than a thread and so, their functioning is simple
  2. The labs keep iterating through their list of TAs to check if there is someone who has not hit their limits on the number of tutorials yet
  3. If there is, then we start searching all over again. 
  4. If not however, then the lab cannot offer TAs anymore and so, exits from the simulation while setting the value `lab->available = 0`

**Note:**

The simulation is said to end when all the students have exited it. We do not care about a lab thread or a course thread exiting the simulation. In fact, since we only take tutorials if there is at least one student who wants the course, the course thread and consequently the lab thread would infinitely wait for a student to pick the course as his preference which in turn is impossible if all students finished their simulation run. So, we cancel any course or lab threads at the end after we join all the student threads.
